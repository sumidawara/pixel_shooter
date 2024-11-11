#include "stdafx.h"
#include "Player.h"

#include "AssetKey.h"
#include "DebugSetting.h"
#include "Bullet/Bullet.h"
#include "GraphicSetting.h"
#include "CollisionUtil.h"
#include "Particle/DamageAmountParticle.h"
#include "Enemy/IEnemy.h"
#include "God.h"
#include "PlayerState.h"
#include "PlayerStateManager.h"
#include "ShotManager.h"

struct Player::Impl
{
	RectF _rectf;

	static constexpr int32 AnimationFrame = 24;
	static constexpr int32 AnimationIndexCount = 4;
	FrameSequencer _animation_frame_sequencer{AnimationFrame, AnimationIndexCount};

	bool _is_right_face = false;
	Vec2 _move_amount = {};
	bool _is_run = false;

	std::shared_ptr<PlayerStateManager> _ptr_player_state_manager;

	ShotManager _shot_manager;

	void move(double delta_time)
	{
		double d = _ptr_player_state_manager->getPlayerState().move_speed * delta_time;

		_move_amount = {0.0, 0.0};

		//上に移動
		if (KeyW.pressed())
		{
			Vec2 delta = {0.0, -d};
			_rectf.moveBy(delta);
			_move_amount += delta;
			_is_run = true;
		}

		//下に移動
		if (KeyS.pressed())
		{
			Vec2 delta = {0.0, d};
			_rectf.moveBy(delta);
			_move_amount += delta;
			_is_run = true;
		}

		//左に移動
		if (KeyA.pressed())
		{
			Vec2 delta = {-d, 0.0};
			_rectf.moveBy(delta);
			_move_amount += delta;
			_is_run = true;
			_is_right_face = false;
		}

		//右に移動
		if (KeyD.pressed())
		{
			Vec2 delta = {d, 0.0};
			_rectf.moveBy(delta);
			_move_amount += delta;
			_is_run = true;
			_is_right_face = true;
		}

		if ((not KeyW.pressed()) && (not KeyA.pressed()) && (not KeyS.pressed()) && (not KeyD.pressed()))
		{
			Vec2 delta = {0.0, 0.0};
			_is_run = false;
		}
	}

	//PlayerStateManagerに移動すべき
	void onDamaged(int32 damage_from_enemy)
	{
		bool is_invincible = _ptr_player_state_manager->getPlayerState().is_invincible;
		if (not is_invincible)
		{
			//HP更新
			auto player_state = _ptr_player_state_manager->getPlayerState();
			int32 damage_amount = damage_from_enemy - player_state.defence;
			if (damage_amount < 0) damage_amount = 0;
			_ptr_player_state_manager->setCurrentHP(player_state.current_hp - damage_amount);

			//DamageAmountEffect
			std::shared_ptr<DamageAmountParticle> ptr_damage_amount_particle = std::make_shared<DamageAmountParticle>();
			ptr_damage_amount_particle->init(_rectf.center(), damage_amount);
			God::getInstance().getPtrParticleManager()->addParticle(ptr_damage_amount_particle);

			if (player_state.current_hp < 0)
			{
				_ptr_player_state_manager->setCurrentHP(0);
			}
			_ptr_player_state_manager->setIsInvincible(true);
		}
	}
};

Player::Player() : p_impl(std::make_shared<Impl>())
{
}

void Player::init(Vec2 pos)
{
	setCenterPos(pos);

	p_impl->_ptr_player_state_manager = std::make_shared<PlayerStateManager>();
	p_impl->_ptr_player_state_manager->init();

	p_impl->_shot_manager.init();
}

void Player::update(double delta_time)
{
	p_impl->move(delta_time);
	p_impl->_ptr_player_state_manager->update(delta_time);
	p_impl->_animation_frame_sequencer.update(delta_time);
	p_impl->_shot_manager.update(delta_time);
}

void Player::draw() const
{
	//無敵の時は点滅
	bool is_invincible = p_impl->_ptr_player_state_manager->getPlayerState().is_invincible;
	double alpha = (is_invincible) ? Periodic::Square0_1(0.1) : 1.0;

	//立ち・歩きのスプライトアニメーション
	if (p_impl->_is_run)
	{
		int32 NORMAL_TILE_WIDTH = GraphicSetting::getNormalTileWidth();
		int32 NORMAL_TILE_HEIGHT = GraphicSetting::getNormalTileHeight();
		TextureAsset(AssetKey::liebesrechner_run)(
				p_impl->_animation_frame_sequencer.getCurrentIndex() * NORMAL_TILE_WIDTH,
				0,
				NORMAL_TILE_WIDTH,
				NORMAL_TILE_HEIGHT)
			.mirrored(p_impl->_is_right_face)
			.drawAt(p_impl->_rectf.center(), ColorF{1.0, alpha});
	}
	else
	{
		TextureAsset(AssetKey::liebesrechner_stand)
			.mirrored(p_impl->_is_right_face)
			.drawAt(p_impl->_rectf.center(), ColorF{1.0, alpha});
	}

	//衝突判定の描画
	if (DebugSetting::getIsCollisionRectVisible())
	{
		p_impl->_rectf.draw(DebugSetting::getCollisionColor());
	}
}

void Player::onCollision(const ICollidable& other)
{
	switch (other.getType())
	{
	case T_Enemy:
		{
			auto ptr_enemy = dynamic_cast<const IEnemy*>(&other);
			p_impl->onDamaged(ptr_enemy->getCollisionDamage());
		}
		break;
	case T_Block:
		CollisionUtil::pushOutFromRectCollision(p_impl->_rectf, other);
		break;
	case T_Bullet:
		break;
	}
}

RectF Player::getBoundingShape() const
{
	return p_impl->_rectf;
}

ICollidableType Player::getType() const
{
	return T_Player;
}

void Player::setCenterPos(Vec2 center_pos)
{
	int32 _original_offset_left = 6; // 当たり判定は実際の画像より左に5pxずれる
	int32 _original_offset_right = 6;
	int32 _original_offset_top = 3;
	int32 _original_offset_bottom = 2;

	p_impl->_rectf = RectF(
		Arg::center_<Vec2>(center_pos),
		(GraphicSetting::getOriginalTileWidth() - _original_offset_left - _original_offset_right) *
		GraphicSetting::getScaleRate(),
		(GraphicSetting::getOriginalTileHeight() - _original_offset_top - _original_offset_bottom) *
		GraphicSetting::getScaleRate()
	);
}

Vec2 Player::getCenterPos() const
{
	return Vec2{p_impl->_rectf.centerX(), p_impl->_rectf.centerY()};
}

RectF Player::getRect() const
{
	return p_impl->_rectf;
}

Vec2 Player::getTargetDirection() const
{
	auto camera_mat3x2 = God::getInstance().getCamera().getMat3x2().inverse();
	auto cursorWorldPos = camera_mat3x2.transformPoint(Cursor::PosF());
	return Vec2{cursorWorldPos - p_impl->_rectf.center()}.normalize();
}

bool Player::getIsRightFace() const
{
	return p_impl->_is_right_face;
}

PlayerState Player::getPlayerState() const
{
	return p_impl->_ptr_player_state_manager->getPlayerState();
}

std::shared_ptr<PlayerStateManager> Player::getPtrPlayerStateManager() const
{
	return p_impl->_ptr_player_state_manager;
}
