#pragma once
#include "BulletContext.h"
#include "../Particle/ParticleManager.h"
#include "../ICollidable.h"

class Bullet : public ICollidable
{
public:
	Bullet();
	void init(BulletContext bullet_context);
	void update(double delta_time);
	void draw() const;

	//ICollidable
	std::variant<RectF, Circle> getBoundingShape() const override;
	void onCollision(const ICollidable& other) override;
	ICollidableType getType() const override;

	bool getIsActive() const;

	int32 getCollisionDamage() const;
	ICollidableType getOwnerType() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

