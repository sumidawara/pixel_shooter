#pragma once

struct PlayerState
{
	int32 max_hp = 0;
	int32 current_hp = 0;
	int32 defence = 0;
	int32 collision_damage = 0;
	double move_speed = 0.0;

	int32 level = 0;
	int32 current_exp = 0;

	//ShotManagerが使用するパラメーター
	double shot_interval = 0.0;
	int32 n_way_front_shot = 0;
	int32 n_way_side_shot = 0;
	int32 n_way_back_shot = 0;
	double reload_interval = 0.0;
	double ammo_capacity = 0;

	//Bulletが使用するパラメーター
	int32 ranged_damage = 0;
	double bullet_range = 0;
	double bullet_size = 0;
	double bullet_speed = 0;
	int32 reflection_count = 0;
	int32 penetration_count = 0;

	double invincible_time = 0.0;
	bool is_invincible = false;
};
