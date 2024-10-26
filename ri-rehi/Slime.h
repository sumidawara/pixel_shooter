#pragma once
#include "FrameSequencer.h"
#include "IEnemyBehavior.h"
#include "IEnemy.h"
#include "StillBehavior.h"
#include "ChasePlayerBehavior.h"
#include "WanderBehavior.h"
#include "Player/Player.h"

class Slime : public IEnemy
{
public:
	Slime();
    void init(Vec2 pos) override;
	void update(double delta_time) override;
	void draw() const override;

	//ICollidable
	void onCollision(const ICollidable& other) override;
	RectF getBoundingShape() const override;
	ICollidableType getType() const override;

	//IEnemy
	int32 getCollisionDamage() const override;
	bool getIsActive() const override;

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;
};

