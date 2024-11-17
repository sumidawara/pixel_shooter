#pragma once
#include "Bullet/BulletContext.h"

struct MobAIContext
{
	MobAIContext(
		RectF& _enemy_rectf,
		double walk_speed,
		double run_speed,
		double view_range,
		Vec2& direction,

		RectF player_rectf,

		BulletContext bullet_context
	);

	//敵自身のデータ
	RectF& enemy_rectf;
	double walk_speed;
	double run_speed;
	double view_range;
	Vec2& direction;

	//プレイヤーのデータ
	RectF player_rectf;

	BulletContext bullet_context;

	//地形データ
};

