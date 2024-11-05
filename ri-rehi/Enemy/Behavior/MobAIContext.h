#pragma once

struct MobAIContext
{
	MobAIContext(
		RectF& _enemy_rectf,
		double walk_speed,
		double run_speed,
		double view_range,
		Vec2& direction,

		RectF player_rectf
	);

	//敵自身のデータ
	RectF& enemy_rectf;
	double walk_speed;
	double run_speed;
	double view_range;
	Vec2& direction;

	//プレイヤーのデータ
	RectF player_rectf;

	//地形データ
};

