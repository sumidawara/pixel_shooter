#include "stdafx.h"
#include "EnemyManager.h"
#include "God.h"
#include "Slime.h"

struct EnemyManager::Impl
{
	std::vector<std::shared_ptr<IEnemy>> _ptr_slime_list;
};

EnemyManager::EnemyManager() : p_impl(std::make_shared<Impl>())
{
}

void EnemyManager::init()
{
	std::shared_ptr<Slime> _ptr_slime1 = std::make_shared<Slime>();
	std::shared_ptr<Slime> _ptr_slime2 = std::make_shared<Slime>();
	_ptr_slime1->init({500, 500});
	_ptr_slime2->init({650, 500});

	p_impl->_ptr_slime_list.push_back(_ptr_slime1);
	p_impl->_ptr_slime_list.push_back(_ptr_slime2);

	auto collision_manager = God::getInstance().getPtrCollisionManager();
	collision_manager->addICollidable(_ptr_slime1);
	collision_manager->addICollidable(_ptr_slime2);
}

void EnemyManager::update(double delta_time)
{
	for(auto ptr_slime : p_impl->_ptr_slime_list)
	{
		ptr_slime->update(delta_time);
	}

	for (auto it = p_impl->_ptr_slime_list.begin(); it != p_impl->_ptr_slime_list.end();)
	{
		bool is_active = (*it)->getIsActive();

		if (not is_active)
		{
			// ICollidableListからも削除
			auto collision_manager = God::getInstance().getPtrCollisionManager();
			collision_manager->removeICollidable(*it);

			it = p_impl->_ptr_slime_list.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void EnemyManager::draw() const
{
	for(auto ptr_slime : p_impl->_ptr_slime_list)
	{
		ptr_slime->draw();
	}
}
