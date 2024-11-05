#include "stdafx.h"
#include "BulletManager.h"
#include "BulletManager.h"
#include "God.h"

struct BulletManager::Impl
{
	std::vector<std::shared_ptr<Bullet>> _bullet_ptr_list;
};

BulletManager::BulletManager() : p_impl(std::make_shared<Impl>())
{
}

void BulletManager::init()
{
}

void BulletManager::update(double delta_time)
{
	for (auto& ptr_bullet : p_impl->_bullet_ptr_list)
	{
		ptr_bullet->update(delta_time);
	}

	for (auto it = p_impl->_bullet_ptr_list.begin(); it != p_impl->_bullet_ptr_list.end();)
	{
		bool is_bullet_active = (*it)->getIsActive();

		if (not is_bullet_active)
		{
			// ICollidableListからも削除
			auto collision_manager = God::getInstance().getPtrCollisionManager();
			collision_manager->removeICollidable(*it);

			it = p_impl->_bullet_ptr_list.erase(it);
		}
		else
		{
			it++;
		}
	}

}

void BulletManager::draw() const
{
	for (auto& ptr_bullet : p_impl->_bullet_ptr_list)
	{
		ptr_bullet->draw();
	}
}

void BulletManager::addBullet(std::shared_ptr<Bullet> ptr_bullet)
{
	p_impl->_bullet_ptr_list.push_back(ptr_bullet);

	//ICollidableListにも追加
	auto collision_manager = God::getInstance().getPtrCollisionManager();
	collision_manager->addICollidable(ptr_bullet);
}

void BulletManager::removeBullet(const std::shared_ptr<Bullet>& ptr_bullet)
{
	auto bullet_it = std::find(p_impl->_bullet_ptr_list.begin(), p_impl->_bullet_ptr_list.end(), ptr_bullet);

	if (bullet_it != p_impl->_bullet_ptr_list.end())
	{
		p_impl->_bullet_ptr_list.erase(bullet_it);
	}
}

void BulletManager::clearBullet()
{
	p_impl->_bullet_ptr_list.clear();
}

std::vector<std::shared_ptr<Bullet>>& BulletManager::getBulletPtrList()
{
	return p_impl->_bullet_ptr_list;
}
