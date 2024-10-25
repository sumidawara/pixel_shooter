#include "stdafx.h"
#include "CollisionUtil.h"

void CollisionUtil::pushOutFromRectCollision(RectF& self_rectf, const ICollidable& other)
{
	auto other_shape = other.getBoundingShape();
	if (auto other_rectf = std::get_if<RectF>(&other_shape))
	{
		auto overlapRectF = self_rectf.getOverlap(*other_rectf);

		if (overlapRectF.size.x <= overlapRectF.size.y)
		{
			if (self_rectf.x <= other_rectf->x)
			{
				self_rectf.moveBy(Vec2{ -overlapRectF.size.x, 0.0f });
			}
			else
			{
				self_rectf.moveBy(Vec2{ overlapRectF.size.x, 0.0f });
			}
		}
		else
		{
			if (self_rectf.y <= other_rectf->y)
			{
				self_rectf.moveBy(Vec2{ 0.0f , -overlapRectF.size.y });
			}
			else
			{
				self_rectf.moveBy(Vec2{ 0.0f , overlapRectF.size.y });
			}
		}
	}
}

void CollisionUtil::pushOutFromRectCollision(const std::shared_ptr<RectF>& ptr_self_rectf, const ICollidable& other)
{
	auto other_shape = other.getBoundingShape();
	if (auto other_rectf = std::get_if<RectF>(&other_shape))
	{
		auto overlapRectF = ptr_self_rectf->getOverlap(*other_rectf);

		if (overlapRectF.size.x <= overlapRectF.size.y)
		{
			if (ptr_self_rectf->x <= other_rectf->x)
			{
				ptr_self_rectf->moveBy(Vec2{ -overlapRectF.size.x, 0.0f });
			}
			else
			{
				ptr_self_rectf->moveBy(Vec2{ overlapRectF.size.x, 0.0f });
			}
		}
		else
		{
			if (ptr_self_rectf->y <= other_rectf->y)
			{
				ptr_self_rectf->moveBy(Vec2{ 0.0f , -overlapRectF.size.y });
			}
			else
			{
				ptr_self_rectf->moveBy(Vec2{ 0.0f , overlapRectF.size.y });
			}
		}
	}
}

DirectionType CollisionUtil::getCollisionFace(RectF& self_rectf, const ICollidable& other)
{
	auto other_shape = other.getBoundingShape();
	if (auto other_rectf = std::get_if<RectF>(&other_shape))
	{
		auto dir = self_rectf.center() - other_rectf->center();

		//上か下かに存在
		if(dir.y >= dir.x)
		{
			if(dir.cross(Vector2D<double>::Up(1)) >= 0)
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
			if(dir.cross(Vector2D<double>::Right(1)) >= 0)
			{
				return Dir_Right;
			}
			else
			{
				return Dir_Left;
			}
		}

	}
	else
	{
		throw Error(U"Error in CollisionUtil::getCollisionFace");
	}
}
