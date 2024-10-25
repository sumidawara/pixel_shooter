#pragma once
#include "Enum.h"

class ICollidable
{
public:
	virtual ~ICollidable() = default;
	virtual std::variant<RectF, Circle> getBoundingShape() const = 0;
	virtual void onCollision(const ICollidable& other) = 0;
	virtual ICollidableType getType() const = 0;
};

