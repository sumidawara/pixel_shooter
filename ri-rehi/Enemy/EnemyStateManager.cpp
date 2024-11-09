#include "stdafx.h"
#include "EnemyStateManager.h"

#include "Debug.h"
#include "God.h"
#include "Particle/DamageAmountParticle.h"
#include "Particle/SparkleParticle.h"

struct EnemyStateManager::Impl
{
	EnemyState _state;

	RectF _rectf;
	Vec2 _direction;

	void calcParameterFromLevel(int32 level)
	{
		//レベルに応じて変化するパラメーターの初期化
		_state.max_hp = _state.basic_max_hp * level;
		_state.current_hp = _state.basic_max_hp * level;
		_state.defence = _state.basic_defence * level;
		_state.collision_damage = _state.basic_collision_damage * level;
		_state.drop_exp = _state.basic_drop_exp * level;
	}

	void generateSparkle_if_hasKey(double delta_time)
	{
		if(_state.has_key)
		{
			_state.sparkle_accumulated_time += delta_time;
			if(_state.sparkle_threshold_time < _state.sparkle_accumulated_time)
			{
				_state.sparkle_accumulated_time -= _state.sparkle_threshold_time;

				double random_distance = Random(_state.inner_circle_range, _state.outer_circle_range);
				double angle = Random(0.0, 2 * Math::Pi);
				double x = _rectf.centerX() + random_distance * Math::Cos(angle);
				double y = _rectf.centerY() + random_distance * Math::Sin(angle);

				//キラキラパーティクル
				auto ptr_sparkle_particle = std::make_shared<SparkleParticle>();
				ptr_sparkle_particle->init(Vec2{x, y});
				God::getInstance().getPtrParticleManager()->addParticle(ptr_sparkle_particle);
			}
		}
	}

	void onDamaged(int32 received_damage)
	{
		int32 damage_amount = received_damage - _state.defence;
		if(damage_amount < 0) damage_amount = 0;
		_state.current_hp -= damage_amount;

		//パーティクルを発生
		auto ptr_damage_amount_particle = std::make_shared<DamageAmountParticle>();
		ptr_damage_amount_particle->init(_rectf.center(), damage_amount);
		God::getInstance().getPtrParticleManager()->addParticle(ptr_damage_amount_particle);

		if (_state.current_hp < 0)
		{
			_state.current_hp = 0;
			onKilled();
			_state.is_active = false;
		};
	}

	void onKilled()
	{
		if(_state.has_key)
		{
			//鍵持ちの場合はEnemyManagerのOnKeyEnemyDeath()を呼ぶ
			auto enemy_manager = God::getInstance().getEnemyManager();
			enemy_manager->onKeyEnemyDeath();
		}

		//経験値をプレイヤーに与える
		auto ptr_player_state_manager = God::getInstance().getPlayer().getPtrPlayerStateManager();
		ptr_player_state_manager->addExp(_state.drop_exp);
	}

	void judgeIsRightFace()
	{

		if (0 <= _direction.x)
		{
			_state.is_right_face = true;
		}
		else
		{
			_state.is_right_face = false;
		}
	}

	void judgeDirection(Vec2 vec)
	{
		std::vector<Vec2> dir = {{1,1},{1,-1},{-1,-1},{-1,1}};

		//右
		if(0 <= vec.cross(dir[0]) && vec.cross(dir[1]) < 0)
		{
			_state.direction_index = 1;
			return;
		}

		//上
		if(0 <= vec.cross(dir[1]) && vec.cross(dir[2]) < 0)
		{
			_state.direction_index = 0;
			return;
		}

		//左
		if(0 <= vec.cross(dir[2]) && vec.cross(dir[3]) < 0)
		{
			_state.direction_index = 3;
			return;
		}

		//下
		if(0 <= vec.cross(dir[3]) && vec.cross(dir[0]) < 0)
		{
			_state.direction_index = 2;
			return;
		}
	}
};

EnemyStateManager::EnemyStateManager() : p_impl(std::make_shared<Impl>())
{
}

void EnemyStateManager::init(const EnemyState& enemy_state, int32 level)
{
	p_impl->_state = enemy_state;

	p_impl->calcParameterFromLevel(level);
}

void EnemyStateManager::update(double delta_time)
{
	p_impl->generateSparkle_if_hasKey(delta_time);
	p_impl->judgeIsRightFace();
	p_impl->judgeDirection(p_impl->_direction);
}

void EnemyStateManager::draw() const
{
}

void EnemyStateManager::onDamaged(int32 received_damage)
{
	p_impl->onDamaged(received_damage);
}

EnemyState EnemyStateManager::getEnemyState()
{
	return p_impl->_state;
}

void EnemyStateManager::setRectf(const RectF& rectf)
{
	p_impl->_rectf = rectf;
}

void EnemyStateManager::setDirection(Vec2 direction)
{
	//Debug::getInstance().writeline(0, Format(direction));
	p_impl->_direction = direction;
}

void EnemyStateManager::setHasKey(bool has_key)
{
	p_impl->_state.has_key = has_key;
}
