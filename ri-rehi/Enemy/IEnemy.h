#pragma once
#include "ICollidable.h"
class IEnemy : public ICollidable
{
public:
	virtual ~IEnemy() = default;
	virtual void init(Vec2 pos, int32 level) = 0;
	virtual void update(double delta_time) = 0;
	virtual void draw() const = 0;

	virtual void setHasKey(bool value) = 0;

	virtual int32 getCollisionDamage() const = 0;
	virtual bool getIsActive() const = 0;
	virtual bool getHasKey() const = 0;

private:
};

