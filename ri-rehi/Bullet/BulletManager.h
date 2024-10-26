#pragma once
#include "Bullet.h"

class BulletManager
{
public:
	BulletManager();

	void update(double delta_time);
	void draw() const;

	void addBullet(std::shared_ptr<Bullet> ptr_bullet);
	void removeBullet(const std::shared_ptr<Bullet>& ptr_bullet);

	std::vector<std::shared_ptr<Bullet>>& getBulletPtrList();

private:
	std::vector<std::shared_ptr<Bullet>> _bullet_ptr_list;
};
