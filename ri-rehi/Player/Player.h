#pragma once
#include "FrameSequencer.h"
#include "Bullet/BulletManager.h"
#include "GraphicSetting.h"
#include "ICollidable.h"
#include "PlayerState.h"
#include "PlayerStateManager.h"

class Player : public ICollidable
{
public:
	Player();
    void init(Vec2 pos);
	void update(double delta_time);
	void draw() const;

	void onCollision(const ICollidable& other) override;
	std::variant<RectF, Circle> getBoundingShape() const override;
	ICollidableType getType() const override;

	Vec2 getCenterPos() const;
	RectF getRect() const;

	PlayerState getPlayerState() const;
	std::shared_ptr<PlayerStateManager> getPtrPlayerStateManager() const;

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;
};

