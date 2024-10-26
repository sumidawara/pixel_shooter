#include "stdafx.h"
#include "CollisionUtil.h"

void CollisionUtil::pushOutFromRectCollision(RectF& self_rectf, const ICollidable& other)
{
	auto other_rectf = other.getBoundingShape();
	auto overlap_rectf = self_rectf.getOverlap(other_rectf);

	if (overlap_rectf.size.x <= overlap_rectf.size.y)
	{
		if (self_rectf.x <= other_rectf.x)
		{
			self_rectf.moveBy(Vec2{-overlap_rectf.size.x, 0.0f});
		}
		else
		{
			self_rectf.moveBy(Vec2{overlap_rectf.size.x, 0.0f});
		}
	}
	else
	{
		if (self_rectf.y <= other_rectf.y)
		{
			self_rectf.moveBy(Vec2{0.0f, -overlap_rectf.size.y});
		}
		else
		{
			self_rectf.moveBy(Vec2{0.0f, overlap_rectf.size.y});
		}
	}
}

void CollisionUtil::pushOutFromRectCollision(const std::shared_ptr<RectF>& ptr_self_rectf, const ICollidable& other)
{
	auto other_rectf = other.getBoundingShape();
	auto overlap_rectf = ptr_self_rectf->getOverlap(other_rectf);

	if (overlap_rectf.size.x <= overlap_rectf.size.y)
	{
		if (ptr_self_rectf->x <= other_rectf.x)
		{
			ptr_self_rectf->moveBy(Vec2{-overlap_rectf.size.x, 0.0f});
		}
		else
		{
			ptr_self_rectf->moveBy(Vec2{overlap_rectf.size.x, 0.0f});
		}
	}
	else
	{
		if (ptr_self_rectf->y <= other_rectf.y)
		{
			ptr_self_rectf->moveBy(Vec2{0.0f, -overlap_rectf.size.y});
		}
		else
		{
			ptr_self_rectf->moveBy(Vec2{0.0f, overlap_rectf.size.y});
		}
	}
}

DirectionType CollisionUtil::getCollisionFace(RectF& self_rectf, const ICollidable& other)
{
	auto other_rectf = other.getBoundingShape();
	auto dir = self_rectf.center() - other_rectf.center();

	//上か下かに存在
	if (dir.y >= dir.x)
	{
		if (dir.cross(Vector2D<double>::Up(1)) >= 0)
		{
			return Dir_Up;
		}
		else
		{
			return Dir_Down;
		}
	}
	//右か下かに存在
	else
	{
		if (dir.cross(Vector2D<double>::Right(1)) >= 0)
		{
			return Dir_Right;
		}
		else
		{
			return Dir_Left;
		}
	}
}
