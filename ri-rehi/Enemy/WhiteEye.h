#pragma once
#include "FrameSequencer.h"
#include "Behavior/IEnemyBehavior.h"
#include "IEnemy.h"
#include "Behavior/StillBehavior.h"
#include "Behavior/ChasePlayerBehavior.h"
#include "Behavior/WanderBehavior.h"
#include "Player/Player.h"

class WhiteEye : public IEnemy
{
public:
	WhiteEye();
	void init(Vec2 pos, int32 level) override;
	void update(double delta_time) override;
	void draw() const override;

	//ICollidable
	void onCollision(const ICollidable& other) override;
	RectF getBoundingShape() const override;
	ICollidableType getType() const override;

	//IEnemy
	int32 getCollisionDamage() const override;
	bool getIsActive() const override;

	bool getHasKey() const override;
	void setHasKey(bool value) override;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

