#include "stdafx.h"
#include "WanderBehavior.h"
#include "MathEx.h"

void WanderBehavior::execute(MobAIContext& mob_ai_context, double delta_time)
{
	Vec2 move_amount = mob_ai_context.direction * mob_ai_context.walk_speed * delta_time;
	mob_ai_context.enemy_rectf.moveBy(move_amount);

	_accumulated_time += delta_time;
	if (WANDERING_THRESHOLD_TIME < _accumulated_time)
	{
		_accumulated_time -= WANDERING_THRESHOLD_TIME;
		mob_ai_context.direction = MathEx::randomVec2(1.0);
	}
}
