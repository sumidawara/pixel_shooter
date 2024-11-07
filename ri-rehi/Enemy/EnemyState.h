#pragma once

struct EnemyState
{
	//mutable parameter
	int32 basic_max_hp = 5;
	int32 basic_defence = 0;
	int32 basic_collision_damage = 2;
	int32 basic_drop_exp = 1;

	int32 max_hp;
	int32 current_hp;
	int32 defence;
	int32 collision_damage;
	int32 drop_exp;

	//immutable parameter
	double walk_speed = 50.0;
	double run_speed = 100.0;
	double view_range = 500.0;



	bool is_active = true;
	bool is_right_face = false;
	bool has_key = false;

	//sparkle particle のパラメーター
	double inner_circle_range = 50;
	double outer_circle_range = 80;
	double sparkle_accumulated_time = 0.0;
	double sparkle_threshold_time = 0.2;

};
