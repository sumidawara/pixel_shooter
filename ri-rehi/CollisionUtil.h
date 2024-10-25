#pragma once
#include "ICollidable.h"

class CollisionUtil
{
public:
	//この方法は衝突したときに片方が片方に完全に飲み込まれないようになっていることが条件
	static void pushOutFromRectCollision(RectF& self_rectf, const ICollidable& other);
	static void pushOutFromRectCollision(const std::shared_ptr<RectF>& ptr_self_rectf, const ICollidable& other);

	//弾の反射に使用
	static DirectionType getCollisionFace(RectF& self_rectf, const ICollidable& other);
private:
};

