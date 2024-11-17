#include "stdafx.h"
#include "WhiteEye.h"

#include "AssetKey.h"
#include "GraphicSetting.h"
#include "DebugSetting.h"
#include "CollisionUtil.h"
#include "Debug.h"
#include "EnemyStateManager.h"
#include "Particle/DamageAmountParticle.h"
#include "God.h"
#include "Behavior/GridChaseBehavior.h"

struct WhiteEye::Impl
{
	RectF _rectf;
	Vec2 _direction{-1.0, 0.0};

	EnemyStateManager _enemy_state_manager;

	std::shared_ptr<StillBehavior> _ptr_still_behavior;
	std::shared_ptr<GridChaseBehavior> _ptr_grid_chase_behavior;
	std::shared_ptr<IEnemyBehavior> _ptr_behavior;

	void plan()
	{
		auto player = God::getInstance().getPlayer();
		double distance = _rectf.center().distanceFrom(player.getCenterPos());
		double NEAR = 50;
		auto state = _enemy_state_manager.getEnemyState();

		if (state.view_range <= distance)
		{
			_ptr_behavior = _ptr_grid_chase_behavior;
		}
		else if (NEAR <= distance and distance <= (state.view_range))
		{
			_ptr_behavior = _ptr_grid_chase_behavior;
		}
		else if (distance <= NEAR)
		{
			_ptr_behavior = _ptr_still_behavior;
		}
	}
};

WhiteEye::WhiteEye(): p_impl(std::make_shared<Impl>())
{
}

void WhiteEye::init(Vec2 pos, int32 level)
{
	//EnemyStateManagerの初期化
	EnemyState context;
	context.basic_max_hp = 5;
	context.basic_defence = 0;
	context.basic_collision_damage = 2;
	context.basic_drop_exp = 1;
	context.walk_speed = 350;
	context.run_speed = 350;
	context.view_range = 500;
	p_impl->_enemy_state_manager.init(context, level);

	//behaviorの初期化
	p_impl->_ptr_still_behavior = std::make_shared<StillBehavior>();
	p_impl->_ptr_grid_chase_behavior = std::make_shared<GridChaseBehavior>();
	p_impl->_ptr_behavior = p_impl->_ptr_still_behavior;

	p_impl->_rectf = {
		pos,
		GraphicSetting::getNormalTileWidth(),
		GraphicSetting::getNormalTileHeight()
	};
}

void WhiteEye::update(double delta_time)
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
}

void WhiteEye::draw() const
{
	auto state = p_impl->_enemy_state_manager.getEnemyState();

	int32 NORMAL_WIDTH = GraphicSetting::getNormalTileWidth();
	int32 NORMAL_HEIGHT = GraphicSetting::getNormalTileHeight();
	TextureAsset(AssetKey::white_eye)
		(state.direction_index * NORMAL_WIDTH, 0, NORMAL_WIDTH, NORMAL_HEIGHT)
		.drawAt(p_impl->_rectf.center());


	Debug::getInstance().writeline(0, Format(state.direction_index));

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

void WhiteEye::onCollision(const ICollidable& other)
{
	switch (other.getType())
	{
	case T_Player:
		break;
	case T_Enemy:
		break;
	case T_Block:
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

RectF WhiteEye::getBoundingShape() const
{
	return p_impl->_rectf;
}

ICollidableType WhiteEye::getType() const
{
	return T_Enemy;
}

void WhiteEye::setHasKey(bool value)
{
	p_impl->_enemy_state_manager.setHasKey(value);
}

int32 WhiteEye::getCollisionDamage() const
{
	return p_impl->_enemy_state_manager.getEnemyState().collision_damage;
}

bool WhiteEye::getIsActive() const
{
	return p_impl->_enemy_state_manager.getEnemyState().is_active;
}

bool WhiteEye::getHasKey() const
{
	return p_impl->_enemy_state_manager.getEnemyState().has_key;
}
