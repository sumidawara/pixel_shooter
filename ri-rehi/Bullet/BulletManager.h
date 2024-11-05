#pragma once
#include "Bullet.h"

class BulletManager
{
public:
	BulletManager();
	void init();
	void update(double delta_time);
	void draw() const;

	void addBullet(std::shared_ptr<Bullet> ptr_bullet);
	void removeBullet(const std::shared_ptr<Bullet>& ptr_bullet);
	void clearBullet();

	std::vector<std::shared_ptr<Bullet>>& getBulletPtrList();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
