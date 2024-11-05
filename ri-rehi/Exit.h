#pragma once
#include "ICollidable.h"

class Exit : public ICollidable
{
public:
	Exit();
	void init(Vec2 pos);
	void update(double delta_time);
	void draw() const;

	virtual RectF getBoundingShape() const override;
	virtual void onCollision(const ICollidable& other) override;
	virtual ICollidableType getType() const override;

	bool getIsLocked() const;
	void setIsLocked(bool value);

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;

};
