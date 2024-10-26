#include "stdafx.h"
#include "PlayerStateManager.h"

#include "Debug.h"
#include "God.h"
#include "PlayerState.h"

struct PlayerStateManager::Impl
{
	std::shared_ptr<PlayerState> _ptr_player_state;

	double _invincible_threshold_time = 0.3;
	double _invincible_accumulated_time = 0.0;

	int32 _writeline_index = 2;

	int32 expCurveFunction(int32 level)
	{
		return Pow(level, 2);
	}

	void updateIsInvincible(double delta_time)
	{
		if (_ptr_player_state->is_invincible)
		{
			_invincible_accumulated_time += delta_time;
			if (_invincible_threshold_time < _invincible_accumulated_time)
			{
				_ptr_player_state->is_invincible = false;
				_invincible_accumulated_time -= _invincible_threshold_time;
			}
		}
	}

	//PlayerStateをPrintできるように実装すべき
	void writelinePlayerState()
	{
		int32 i = _writeline_index;
		Debug::getInstance().writeline(i, U"MaxHP : " + Format(_ptr_player_state->max_hp));
		Debug::getInstance().writeline(i, U"CurrentHP : " + Format(_ptr_player_state->current_hp));
		Debug::getInstance().writeline(i, U"Defence : " + Format(_ptr_player_state->defence));
		Debug::getInstance().writeline(i, U"CollisionDamage : " + Format(_ptr_player_state->collision_damage));
		Debug::getInstance().writeline(i, U"RangedDamage : " + Format(_ptr_player_state->ranged_damage));
		Debug::getInstance().writeline(i, U"MoveSpeed : " + Format(_ptr_player_state->move_speed));
		Debug::getInstance().writeline(i, U"Level : " + Format(_ptr_player_state->level));
		Debug::getInstance().writeline(i, U"CurrentExp : " + Format(_ptr_player_state->current_exp));
		Debug::getInstance().writeline(i, U"ShotInterval : " + Format(_ptr_player_state->shot_interval));
		Debug::getInstance().writeline(i, U"IsInvincible : " + Format(_ptr_player_state->is_invincible));
	}
};

PlayerStateManager::PlayerStateManager() : p_impl(std::make_shared<Impl>())
{
}

void PlayerStateManager::init()
{
	p_impl->_ptr_player_state = std::make_shared<PlayerState>();

	p_impl->_ptr_player_state->max_hp = 20;
	p_impl->_ptr_player_state->current_hp = 20;
	p_impl->_ptr_player_state->defence = 0;
	p_impl->_ptr_player_state->collision_damage = 1;
	p_impl->_ptr_player_state->move_speed = 400.0;

	p_impl->_ptr_player_state->level = 1;
	p_impl->_ptr_player_state->current_exp = 0;

	//ShotManagerのパラメータ
	p_impl->_ptr_player_state->shot_interval = 0.3;
	p_impl->_ptr_player_state->n_way_front_shot = 1;
	p_impl->_ptr_player_state->n_way_side_shot = 0;
	p_impl->_ptr_player_state->n_way_back_shot = 0;
	p_impl->_ptr_player_state->reload_interval = 2.0;
	p_impl->_ptr_player_state->ammo_capacity = 10;

	//Bulletのパラメータ
	p_impl->_ptr_player_state->ranged_damage = 1;
	p_impl->_ptr_player_state->bullet_range = 600;
	p_impl->_ptr_player_state->bullet_size = 10;
	p_impl->_ptr_player_state->bullet_speed = 400;
	p_impl->_ptr_player_state->reflection_count = 2;
	p_impl->_ptr_player_state->penetration_count = 0;

	p_impl->_ptr_player_state->is_invincible = false;
}

void PlayerStateManager::update(double delta_time)
{
	p_impl->updateIsInvincible(delta_time);

	if (Debug::getInstance().getDebugScreenIndex() == p_impl->_writeline_index)
	{
		p_impl->writelinePlayerState();
	}
}

void PlayerStateManager::draw() const
{
}

void PlayerStateManager::enhancePlayerState(const PlayerState& parameter)
{
	auto current_state = p_impl->_ptr_player_state;

	p_impl->_ptr_player_state->max_hp = current_state->max_hp + parameter.max_hp;
	p_impl->_ptr_player_state->defence = current_state->defence + parameter.defence;
	p_impl->_ptr_player_state->collision_damage = current_state->collision_damage + parameter.collision_damage;
	p_impl->_ptr_player_state->ranged_damage = current_state->ranged_damage + parameter.ranged_damage;
	p_impl->_ptr_player_state->move_speed = current_state->move_speed + parameter.move_speed;
}

void PlayerStateManager::addExp(int32 value)
{
	p_impl->_ptr_player_state->current_exp += value;
	int32 needed_exp = p_impl->expCurveFunction(p_impl->_ptr_player_state->level);

	//レベルアップ
	if (needed_exp <= p_impl->_ptr_player_state->current_exp)
	{
		p_impl->_ptr_player_state->current_exp -= needed_exp;
		p_impl->_ptr_player_state->level += 1;

		God::getInstance().getPtrAbilityManager()->rollAbility();
	}
}


void PlayerStateManager::setCurrentHP(int32 value)
{
	p_impl->_ptr_player_state->current_hp = value;
}

void PlayerStateManager::setIsInvincible(bool value)
{
	p_impl->_ptr_player_state->is_invincible = value;
}

int32 PlayerStateManager::getRemainingExpToNextLevelUp() const
{
	return p_impl->expCurveFunction(p_impl->_ptr_player_state->level) - p_impl->_ptr_player_state->current_exp;
}

PlayerState PlayerStateManager::getPlayerState() const
{
	return *p_impl->_ptr_player_state;
}
