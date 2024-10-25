#pragma once
#include "Enum.h"

struct BulletContext
{
	RectF rectf; // この中に bullet_size の情報も入る
	Vec2 direction;
	ICollidableType owner_type;

	double speed;
	double range;
	int32 damage;
	int32 reflection_count;
	int32 penetration_count;
};
