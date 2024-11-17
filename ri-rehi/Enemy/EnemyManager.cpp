#include "stdafx.h"
#include "EnemyManager.h"

#include "Ghost.h"
#include "God.h"
#include "Skelton.h"
#include "Slime.h"
#include "WhiteEye.h"

struct EnemyManager::Impl
{
	std::vector<std::shared_ptr<IEnemy>> _enemy_ptr_list;

	void deleteInactiveEnemy()
	{
		for (auto it = _enemy_ptr_list.begin(); it != _enemy_ptr_list.end();)
		{
			bool is_active = (*it)->getIsActive();

			if (not is_active)
			{
				// ICollidableListからも削除
				auto collision_manager = God::getInstance().getPtrCollisionManager();
				collision_manager->removeICollidable(*it);

				it = _enemy_ptr_list.erase(it);
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
	for(auto ptr_slime : p_impl->_enemy_ptr_list)
	{
		ptr_slime->update(delta_time);
	}
	p_impl->deleteInactiveEnemy();
}

void EnemyManager::draw() const
{
	for(auto ptr_slime : p_impl->_enemy_ptr_list)
	{
		ptr_slime->draw();
	}
}

void EnemyManager::clearEnemy()
{
	p_impl->_enemy_ptr_list.clear();
}

void EnemyManager::createEnemy(EnemyType::EnemyType enemy_type, Vec2 pos)
{
	auto collision_manager = God::getInstance().getPtrCollisionManager();

	switch (enemy_type)
	{
	case EnemyType::Slime:
		{
			auto _ptr_slime = std::make_shared<Slime>();
			_ptr_slime->init(pos, 1);
			p_impl->_enemy_ptr_list.push_back(_ptr_slime);
			collision_manager->addICollidable(_ptr_slime);
		}
		break;
	case EnemyType::WhiteEye:
		{
			auto _ptr_white_eye = std::make_shared<WhiteEye>();
			_ptr_white_eye->init(pos, 1);
			p_impl->_enemy_ptr_list.push_back(_ptr_white_eye);
			collision_manager->addICollidable(_ptr_white_eye);
		}
		break;
	case EnemyType::Ghost:
		{
			auto _ptr_ghost = std::make_shared<Ghost>();
			_ptr_ghost->init(pos, 1);
			p_impl->_enemy_ptr_list.push_back(_ptr_ghost);
			collision_manager->addICollidable(_ptr_ghost);
		}
		break;
	case EnemyType::Skelton:
		{
			auto _ptr_skelton = std::make_shared<Skelton>();
			_ptr_skelton->init(pos, 1);
			p_impl->_enemy_ptr_list.push_back(_ptr_skelton);
			collision_manager->addICollidable(_ptr_skelton);
		}
		break;
	}
}

void EnemyManager::giveKeyToOneEnemy()
{
	auto list_size = static_cast<int32>(p_impl->_enemy_ptr_list.size());
	p_impl->_enemy_ptr_list[Random(0, list_size - 1)]->setHasKey(true);
}

void EnemyManager::onKeyEnemyDeath()
{
	God::getInstance().getPtrExit()->setIsLocked(false);
}
