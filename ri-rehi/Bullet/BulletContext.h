#pragma once
#include "Enum.h"

struct BulletContext
{
	RectF rectf = {}; // この中に bullet_size の情報も入る
	Vec2 direction = {};
	ICollidableType owner_type = T_Enemy;
	ColorF colorf = Palette::White;

	double speed = 100;
	double range = 100;
	int32 damage = 100;
	int32 reflection_count = 0;
	int32 penetration_count = 0;
};
