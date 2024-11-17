#include "stdafx.h"
#include "SkeltonShotBehavior.h"

#include "God.h"

void SkeltonShotBehavior::execute(MobAIContext& mob_ai_context, double delta_time)
{
	shot_accumulated_time += delta_time;

	if(SHOT_THRESHOLD_TIME < shot_accumulated_time)
	{
		shot_accumulated_time -= SHOT_THRESHOLD_TIME;

		auto player = God::getInstance().getPlayer();

		auto direction_to_player = player.getCenterPos() - mob_ai_context.enemy_rectf.center();
		direction_to_player = direction_to_player.normalized();

		BulletContext context;
		context.direction = direction_to_player;
		context.rectf = mob_ai_context.bullet_context.rectf;
		context.owner_type = mob_ai_context.bullet_context.owner_type;
		context.colorf = mob_ai_context.bullet_context.colorf;
		context.speed = mob_ai_context.bullet_context.speed;
		context.range = mob_ai_context.bullet_context.range;
		context.damage = mob_ai_context.bullet_context.damage;
		context.reflection_count = mob_ai_context.bullet_context.reflection_count;
		context.penetration_count = mob_ai_context.bullet_context.penetration_count;

		auto ptr_bullet = std::make_shared<Bullet>();
		ptr_bullet->init(context);
		God::getInstance().getBulletManager()->addBullet(ptr_bullet);
	}
}
