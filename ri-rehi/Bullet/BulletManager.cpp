#include "stdafx.h"
#include "BulletManager.h"
#include "God.h"

BulletManager::BulletManager()
{
}

void BulletManager::update(double delta_time)
{
	for (auto& ptr_bullet : _bullet_ptr_list)
	{
		ptr_bullet->update(delta_time);
	}

	for (auto it = _bullet_ptr_list.begin(); it != _bullet_ptr_list.end();)
	{
		bool is_bullet_active = (*it)->getIsActive();

		if (not is_bullet_active)
		{
			// ICollidableListからも削除
			God::getInstance().removeICollidable(*it);

			it = _bullet_ptr_list.erase(it);
		}
		else
		{
			it++;
		}
	}

}

void BulletManager::draw() const
{
	for (auto& ptr_bullet : _bullet_ptr_list)
	{
		ptr_bullet->draw();
	}
}

void BulletManager::addBullet(std::shared_ptr<Bullet> ptr_bullet)
{
	_bullet_ptr_list.push_back(ptr_bullet);

	//ICollidableListにも追加
	God::getInstance().addICollidable(std::static_pointer_cast<ICollidable>(ptr_bullet));
}

void BulletManager::removeBullet(std::shared_ptr<Bullet> ptr_bullet)
{
	auto bullet_it = std::find(_bullet_ptr_list.begin(), _bullet_ptr_list.end(), ptr_bullet);

	if (bullet_it != _bullet_ptr_list.end())
	{
		_bullet_ptr_list.erase(bullet_it);
	}
}

std::vector<std::shared_ptr<Bullet>>& BulletManager::getBulletPtrList()
{
	return _bullet_ptr_list;
}
