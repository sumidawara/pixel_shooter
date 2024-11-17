#include "stdafx.h"
#include "MobAIContext.h"

MobAIContext::MobAIContext(
	RectF& enemy_rectf,
	double walk_speed,
	double run_speed,
	double view_range,
	Vec2& direction,

	RectF player_rectf,

	BulletContext bullet_context)
	:
	enemy_rectf(enemy_rectf),
	walk_speed(walk_speed),
	run_speed(run_speed),
	view_range(view_range),
	direction(direction),

	player_rectf(player_rectf),

	bullet_context(bullet_context)
{

}
