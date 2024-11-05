#include "stdafx.h"
#include "EnemyManager.h"
#include "God.h"
#include "Slime.h"

struct EnemyManager::Impl
{
	std::vector<std::shared_ptr<IEnemy>> _ptr_enemy_list;

	void deleteInactiveEnemy()
	{
		for (auto it = _ptr_enemy_list.begin(); it != _ptr_enemy_list.end();)
		{
			bool is_active = (*it)->getIsActive();

			if (not is_active)
			{
				// ICollidableListからも削除
				auto collision_manager = God::getInstance().getPtrCollisionManager();
				collision_manager->removeICollidable(*it);

				it = _ptr_enemy_list.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
};

EnemyManager::EnemyManager() : p_impl(std::make_shared<Impl>())
{
}

void EnemyManager::init()
{
}

void EnemyManager::update(double delta_time)
{
	for(auto ptr_slime : p_impl->_ptr_enemy_list)
	{
		ptr_slime->update(delta_time);
	}
	p_impl->deleteInactiveEnemy();
}

void EnemyManager::draw() const
{
	for(auto ptr_slime : p_impl->_ptr_enemy_list)
	{
		ptr_slime->draw();
	}
}

void EnemyManager::clear()
{
	p_impl->_ptr_enemy_list.clear();
}

void EnemyManager::createEnemy(EnemyType::EnemyType enemy_type, Vec2 pos)
{
	switch (enemy_type)
	{
	case EnemyType::Slime:
		auto _ptr_slime = std::make_shared<Slime>();
		_ptr_slime->init(pos);
		p_impl->_ptr_enemy_list.push_back(_ptr_slime);
		auto collision_manager = God::getInstance().getPtrCollisionManager();
		collision_manager->addICollidable(_ptr_slime);
		break;
	}
}
