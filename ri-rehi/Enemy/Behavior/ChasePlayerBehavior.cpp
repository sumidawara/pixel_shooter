#include "stdafx.h"
#include "ChasePlayerBehavior.h"

void ChasePlayerBehavior::execute(MobAIContext& mob_ai_context, double delta_time)
{
	Vec2 targetDir = mob_ai_context.player_rectf.pos - mob_ai_context.enemy_rectf.pos;
	Vec2 move_amount = targetDir.normalize() * mob_ai_context.run_speed * delta_time;

	mob_ai_context.enemy_rectf.moveBy(move_amount);
	mob_ai_context.direction = move_amount.normalized();
}
