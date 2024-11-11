#include "stdafx.h"
#include "GhostChaseBehavior.h"

#include "God.h"

void GhostChaseBehavior::execute(MobAIContext& mob_ai_context, double delta_time)
{
	auto player = God::getInstance().getPlayer();
	Vec2 enemy_target_dir = player.getRect().pos - mob_ai_context.enemy_rectf.pos;

	bool is_right_face;

	if(0 <= enemy_target_dir.x)
	{
		is_right_face = true;
	}
	else
	{
		is_right_face = false;
	}

	//敵の向かう方向とプレイヤの見る方向が向かい合う
	if(is_right_face != player.getIsRightFace())
	{

	}
	else
	{
		Vec2 move_amount = enemy_target_dir.normalize() * mob_ai_context.run_speed * delta_time;
		mob_ai_context.enemy_rectf.moveBy(move_amount);
		mob_ai_context.direction = move_amount.normalized();
	}
}
