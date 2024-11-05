#include "stdafx.h"
#include "Slime.h"

#include "AssetKey.h"
#include "GraphicSetting.h"
#include "DebugSetting.h"
#include "CollisionUtil.h"
#include "Particle/DamageAmountParticle.h"
#include "God.h"

struct Slime::Impl
{
	RectF _rectf;
	Vec2 _direction{-1.0, 0.0};

	bool _is_active = true;
	bool _is_right_face = false;
	bool _has_key = false;

	std::shared_ptr<StillBehavior> _ptr_still_behavior;
	std::shared_ptr<ChasePlayerBehavior> _ptr_chase_player_behavior;
	std::shared_ptr<WanderBehavior> _ptr_wander_behavior;
	std::shared_ptr<IEnemyBehavior> _ptr_behavior;

	//mutable parameter
	int32 _basic_max_hp = 5;
	int32 _basic_defence = 0;
	int32 _basic_collision_damage = 2;
	int32 _basic_drop_exp = 1;

	int32 _max_hp;
	int32 _current_hp;
	int32 _defence;
	int32 _collision_damage;
	int32 _drop_exp;

	//immutable parameter
	double _walk_speed = 50.0;
	double _run_speed = 100.0;
	double _view_range = 500.0;

	void plan()
	{
		auto player = God::getInstance().getPlayer();
		double distance = _rectf.center().distanceFrom(player.getCenterPos());
		double NEAR = 50;

		if (_view_range <= distance)
		{
			_ptr_behavior = _ptr_wander_behavior;
		}
		else if (NEAR <= distance and distance <= _view_range)
		{
			_ptr_behavior = _ptr_chase_player_behavior;
		}
		else if (distance <= NEAR)
		{
			_ptr_behavior = _ptr_still_behavior;
		}
	}

	void onDamaged(int32 raw_damage_received)
	{
		int32 damage_amount = raw_damage_received - _defence;
		if(damage_amount < 0) damage_amount = 0;
		_current_hp -= damage_amount;

		//パーティクルを発生
		std::shared_ptr<DamageAmountParticle> ptr_damage_amount_particle = std::make_shared<DamageAmountParticle>();
		ptr_damage_amount_particle->init(_rectf.center(), damage_amount);
		God::getInstance().getPtrParticleManager()->addParticle(ptr_damage_amount_particle);

		if (_current_hp < 0)
		{
			_current_hp = 0;
			onKilled();
			_is_active = false;
		};
	}

	void onKilled()
	{
		auto ptr_player_state_manager = God::getInstance().getPlayer().getPtrPlayerStateManager();
		ptr_player_state_manager->addExp(_drop_exp);
	}

	void judgeIsRightFace()
	{
		if (0 <= _direction.x)
		{
			_is_right_face = true;
		}
		else
		{
			_is_right_face = false;
		}
	}
};

Slime::Slime(): p_impl(std::make_shared<Impl>())
{
}

void Slime::init(Vec2 pos, int32 level)
{
	//behaviorの初期化
	p_impl->_ptr_still_behavior = std::make_shared<StillBehavior>();
	p_impl->_ptr_chase_player_behavior = std::make_shared<ChasePlayerBehavior>();
	p_impl->_ptr_wander_behavior = std::make_shared<WanderBehavior>();
	p_impl->_ptr_behavior = p_impl->_ptr_still_behavior;

	//レベルに応じて変化するパラメーターの初期化
	p_impl->_max_hp = p_impl->_basic_max_hp * level;
	p_impl->_current_hp = p_impl->_basic_max_hp * level;
	p_impl->_defence = p_impl->_basic_defence * level;
	p_impl->_collision_damage = p_impl->_basic_collision_damage * level;
	p_impl->_drop_exp = p_impl->_basic_drop_exp * level;

	{
		int32 _original_offset_left = 5;
		int32 _original_offset_right = 5;
		int32 _original_offset_top = 17;
		int32 _original_offset_bottom = 1;

		p_impl->_rectf = {
			pos,
			(GraphicSetting::getOriginalTileWidth() - _original_offset_left - _original_offset_right) *
			GraphicSetting::getScaleRate(),
			(GraphicSetting::getOriginalTileHeight() - _original_offset_top - _original_offset_bottom) *
			GraphicSetting::getScaleRate()
		};
	};
}

void Slime::update(double delta_time)
{
	MobAIContext mob_ai_context{
		p_impl->_rectf,
		p_impl->_walk_speed,
		p_impl->_run_speed,
		p_impl->_view_range,
		p_impl->_direction,

		God::getInstance().getPlayer().getRect()
	};

	p_impl->plan();
	p_impl->_ptr_behavior->execute(mob_ai_context, delta_time);

	p_impl->judgeIsRightFace();
}

void Slime::draw() const
{
	TextureAsset(AssetKey::slime).mirrored(p_impl->_is_right_face).drawAt(p_impl->_rectf.center());

	//衝突判定の描画
	if (DebugSetting::getIsCollisionRectVisible())
	{
		p_impl->_rectf.draw(DebugSetting::getCollisionColor());
	}

	if (DebugSetting::getIsViewRangeVisible())
	{
		Circle{p_impl->_rectf.center(), p_impl->_view_range}.draw(DebugSetting::getViewRangeColor());
	}
}

void Slime::onCollision(const ICollidable& other)
{
	auto other_type = other.getType();
	switch (other_type)
	{
	case T_Player:

		break;
	case T_Enemy:
		break;
	case T_Block:
		CollisionUtil::pushOutFromRectCollision(p_impl->_rectf, other);
		break;
	case T_Bullet:
		{
			auto ptr_bullet = dynamic_cast<const Bullet*>(&other);
			if (ptr_bullet->getOwnerType() == T_Player)
			{
				p_impl->onDamaged(ptr_bullet->getCollisionDamage());
			}
		}
		break;
	default:
		break;
	}
}

RectF Slime::getBoundingShape() const
{
	return p_impl->_rectf;
}

ICollidableType Slime::getType() const
{
	return T_Enemy;
}

void Slime::setHasKey(bool value)
{
	p_impl->_has_key = value;
}

int32 Slime::getCollisionDamage() const
{
	return p_impl->_collision_damage;
}

bool Slime::getIsActive() const
{
	return p_impl->_is_active;
}

bool Slime::getHasKey() const
{
	return p_impl->_has_key;
}
