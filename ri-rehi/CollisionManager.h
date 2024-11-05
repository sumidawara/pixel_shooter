#pragma once
#include "ICollidable.h"

class CollisionManager
{
public:
	CollisionManager();
	void init();
	void update(double delta_time);
	void draw() const;

	void clear();

	void addICollidable(const std::shared_ptr<ICollidable>& ptr_icollidable) const;
	void removeICollidable(const std::shared_ptr<ICollidable>& ptr_icollidable);

	std::shared_ptr<std::vector<std::shared_ptr<ICollidable>>> getPtrICollisionList();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
