#include "stdafx.h"
#include "Skelton.h"

#include "AssetKey.h"
#include "GraphicSetting.h"
#include "DebugSetting.h"
#include "CollisionUtil.h"
#include "EnemyState.h"
#include "EnemyStateManager.h"
#include "Particle/DamageAmountParticle.h"
#include "God.h"
#include "Behavior/ChasePlayerBehavior.h"
#include "Behavior/GhostChaseBehavior.h"
#include "Behavior/MobAIContext.h"
#include "Behavior/SkeltonShotBehavior.h"
#include "Behavior/StillBehavior.h"
#include "Behavior/WanderBehavior.h"
#include "Particle/SparkleParticle.h"

struct Skelton::Impl
{
	RectF _rectf;
	Vec2 _direction{-1.0, 0.0};

	int32 _anime_index = 0;

	Vec2 drawOffset;

	EnemyStateManager _enemy_state_manager;

	std::shared_ptr<StillBehavior> _ptr_still_behavior;
	std::shared_ptr<SkeltonShotBehavior> _ptr_skelton_shot_behavior;

	std::shared_ptr<IEnemyBehavior> _ptr_behavior;

	void plan()
	{
		auto player = God::getInstance().getPlayer();
		double distance = _rectf.center().distanceFrom(player.getCenterPos());
		double NEAR = 50;
		auto state = _enemy_state_manager.getEnemyState();

		if (state.view_range <= distance)
		{
			_ptr_behavior = _ptr_skelton_shot_behavior;
		}
		else if (NEAR <= distance and distance <= (state.view_range))
		{
			_ptr_behavior = _ptr_skelton_shot_behavior;
		}
		else if (distance <= NEAR)
		{
			_ptr_behavior = _ptr_still_behavior;
		}
	}
};

Skelton::Skelton(): p_impl(std::make_shared<Impl>())
{

}

void Skelton::init(Vec2 pos, int32 level)
{
	//EnemyStateManagerの初期化
	EnemyState context;
	context.basic_max_hp = 5;
	context.basic_defence = 0;
	context.basic_collision_damage = 2;
	context.basic_drop_exp = 1;
	context.walk_speed = 100;
	context.run_speed = 100;
	context.view_range = 400;
	p_impl->_enemy_state_manager.init(context, level);

	//behaviorの初期化
	p_impl->_ptr_still_behavior = std::make_shared<StillBehavior>();
	p_impl->_ptr_skelton_shot_behavior = std::make_shared<SkeltonShotBehavior>();
	p_impl->_ptr_behavior = p_impl->_ptr_still_behavior;

	p_impl->_rectf = RectF{pos, Vec2{88, 66}};
	p_impl->drawOffset = {-20, -48};
}

void Skelton::update(double delta_time)
{
	//EnemyStateの更新
	p_impl->_enemy_state_manager.setRectf(p_impl->_rectf);
	p_impl->_enemy_state_manager.setDirection(p_impl->_direction);
	p_impl->_enemy_state_manager.update(delta_time);

	auto state = p_impl->_enemy_state_manager.getEnemyState();

	BulletContext bullet_context;
	bullet_context.rectf = RectF{
		Arg::center_<Vec2>(p_impl->_rectf.center()), 10, 10
	};
	bullet_context.direction = Vec2{0, 0};
	bullet_context.owner_type = T_Enemy;
	bullet_context.colorf = Palette::White;
	bullet_context.speed = 200;
	bullet_context.range = 500;
	bullet_context.damage = 5;
	bullet_context.reflection_count = 0;
	bullet_context.penetration_count = 0;

	MobAIContext mob_ai_context{
		p_impl->_rectf,
		state.walk_speed,
		state.run_speed,
		state.view_range,
		p_impl->_direction,

		God::getInstance().getPlayer().getRect(),

		bullet_context
	};
	p_impl->plan();
	p_impl->_ptr_behavior->execute(mob_ai_context, delta_time);
}

void Skelton::draw() const
{
	auto state = p_impl->_enemy_state_manager.getEnemyState();
	auto NORMAL_WIDTH = GraphicSetting::getNormalTileWidth();
	auto NORMAL_HEIGHT = GraphicSetting::getNormalTileHeight();
	TextureAsset(AssetKey::skelton)
		(NORMAL_WIDTH * p_impl->_anime_index, 0, NORMAL_WIDTH, NORMAL_HEIGHT)
		.mirrored(state.is_right_face)
		.draw(p_impl->_rectf.pos + p_impl->drawOffset);

	//衝突判定の描画
	if (DebugSetting::getIsCollisionRectVisible())
	{
		p_impl->_rectf.draw(DebugSetting::getCollisionColor());
	}

	if (DebugSetting::getIsViewRangeVisible())
	{
		Circle{p_impl->_rectf.center(), state.view_range}.draw(DebugSetting::getViewRangeColor());
	}
}

void Skelton::onCollision(const ICollidable& other)
{
	switch (other.getType())
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
				p_impl->_enemy_state_manager.onDamaged(ptr_bullet->getCollisionDamage());
			}
		}
		break;
	default:
		break;
	}
}

RectF Skelton::getBoundingShape() const
{
	return p_impl->_rectf;
}

ICollidableType Skelton::getType() const
{
	return T_Enemy;
}

void Skelton::setHasKey(bool value)
{
	p_impl->_enemy_state_manager.setHasKey(value);
}

int32 Skelton::getCollisionDamage() const
{
	return p_impl->_enemy_state_manager.getEnemyState().collision_damage;
}

bool Skelton::getIsActive() const
{
	return p_impl->_enemy_state_manager.getEnemyState().is_active;
}

bool Skelton::getHasKey() const
{
	return p_impl->_enemy_state_manager.getEnemyState().has_key;
}
