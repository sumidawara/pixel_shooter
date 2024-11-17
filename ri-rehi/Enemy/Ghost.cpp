#include "stdafx.h"
#include "Ghost.h"

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
#include "Behavior/StillBehavior.h"
#include "Behavior/WanderBehavior.h"
#include "Particle/SparkleParticle.h"

struct Ghost::Impl
{
	RectF _rectf;
	Vec2 _direction{-1.0, 0.0};

	int32 _is_hiding = 0;

	Vec2 drawOffset;

	EnemyStateManager _enemy_state_manager;

	std::shared_ptr<StillBehavior> _ptr_still_behavior;
	std::shared_ptr<GhostChaseBehavior> _ptr_ghost_chase_behavior;
	std::shared_ptr<WanderBehavior> _ptr_wander_behavior;
	std::shared_ptr<IEnemyBehavior> _ptr_behavior;

	void plan()
	{
		auto player = God::getInstance().getPlayer();
		double distance = _rectf.center().distanceFrom(player.getCenterPos());
		double NEAR = 50;
		auto state = _enemy_state_manager.getEnemyState();

		if (state.view_range <= distance)
		{
			_ptr_behavior = _ptr_ghost_chase_behavior;
		}
		else if (NEAR <= distance and distance <= (state.view_range))
		{
			_ptr_behavior = _ptr_ghost_chase_behavior;
		}
		else if (distance <= NEAR)
		{
			_ptr_behavior = _ptr_still_behavior;
		}
	}

	void updateIsHiding()
	{
		auto player = God::getInstance().getPlayer();
		auto state = _enemy_state_manager.getEnemyState();

		//向かい合っている場合
		if (state.is_right_face != player.getIsRightFace())
		{
			_is_hiding = 1;
		}
		else
		{
			_is_hiding = 0;
		}
	}
};

Ghost::Ghost(): p_impl(std::make_shared<Impl>())
{
}

void Ghost::init(Vec2 pos, int32 level)
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
	p_impl->_ptr_ghost_chase_behavior = std::make_shared<GhostChaseBehavior>();
	p_impl->_ptr_wander_behavior = std::make_shared<WanderBehavior>();
	p_impl->_ptr_behavior = p_impl->_ptr_still_behavior;

	p_impl->_rectf = RectF{pos, Vec2{88, 66}};
	p_impl->drawOffset = {-20, -48};
}

void Ghost::update(double delta_time)
{
	//EnemyStateの更新
	p_impl->_enemy_state_manager.setRectf(p_impl->_rectf);
	p_impl->_enemy_state_manager.setDirection(p_impl->_direction);
	p_impl->_enemy_state_manager.update(delta_time);

	auto state = p_impl->_enemy_state_manager.getEnemyState();
	BulletContext bullet_context;
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

	p_impl->updateIsHiding();
}

void Ghost::draw() const
{
	auto state = p_impl->_enemy_state_manager.getEnemyState();
	auto NORMAL_WIDTH = GraphicSetting::getNormalTileWidth();
	auto NORMAL_HEIGHT = GraphicSetting::getNormalTileHeight();
	TextureAsset(AssetKey::ghost)
		(NORMAL_WIDTH * p_impl->_is_hiding, 0, NORMAL_WIDTH, NORMAL_HEIGHT)
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

void Ghost::onCollision(const ICollidable& other)
{
	switch (other.getType())
	{
	case T_Player:
		break;
	case T_Enemy:
		break;
	case T_Block:
		//CollisionUtil::pushOutFromRectCollision(p_impl->_rectf, other);
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

RectF Ghost::getBoundingShape() const
{
	return p_impl->_rectf;
}

ICollidableType Ghost::getType() const
{
	return T_Enemy;
}

void Ghost::setHasKey(bool value)
{
	p_impl->_enemy_state_manager.setHasKey(value);
}

int32 Ghost::getCollisionDamage() const
{
	return p_impl->_enemy_state_manager.getEnemyState().collision_damage;
}

bool Ghost::getIsActive() const
{
	return p_impl->_enemy_state_manager.getEnemyState().is_active;
}

bool Ghost::getHasKey() const
{
	return p_impl->_enemy_state_manager.getEnemyState().has_key;
}
