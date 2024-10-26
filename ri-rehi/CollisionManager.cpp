#include "stdafx.h"
#include "CollisionManager.h"

#include "Debug.h"
#include "God.h"

struct CollisionManager::Impl
{
	std::shared_ptr<std::vector<std::shared_ptr<ICollidable>>> _ptr_entity_list;

	int32 _writeline_index = 1;
	int32 _t_block_count = 0;
	int32 _t_player_count = 0;
	int32 _t_bullet_count = 0;
	int32 _t_enemy_count = 0;
	double _accumulated_count_time = 0.0;
	double THRESHOLD_COUNT_TIME = 1.0;

	void checkEntityWithEntity()
	{
		for (int32 i = 0; i < _ptr_entity_list->size(); i++)
		{
			for (int32 j = i; j < _ptr_entity_list->size(); j++)
			{
				if (i != j)
				{
					auto ptr_icollidable_i = (*_ptr_entity_list)[i];
					auto ptr_icollidable_j = (*_ptr_entity_list)[j];

					auto rectf_i = ptr_icollidable_i->getBoundingShape();
					auto rectf_j = ptr_icollidable_j->getBoundingShape();

					bool is_intersecting = rectf_i.intersects(rectf_j);

					if (not is_intersecting) continue;

					ptr_icollidable_i->onCollision(*ptr_icollidable_j);
					ptr_icollidable_j->onCollision(*ptr_icollidable_i);
				}
			}
		}
	}

	void analyzeCollision(double delta_time)
	{
		if (Debug::getInstance().getDebugScreenIndex() == _writeline_index)
		{
			_accumulated_count_time += delta_time;

			if (THRESHOLD_COUNT_TIME < _accumulated_count_time)
			{
				_accumulated_count_time -= THRESHOLD_COUNT_TIME;

				_t_block_count = 0;
				_t_player_count = 0;
				_t_bullet_count = 0;
				_t_enemy_count = 0;

				for (int32 i = 0; i < _ptr_entity_list->size(); i++)
				{
					//ICollidableの数の確認
					switch ((*_ptr_entity_list)[i]->getType())
					{
					case T_Block:
						_t_block_count++;
						break;
					case T_Player:
						_t_player_count++;
						break;
					case T_Bullet:
						_t_bullet_count++;
						break;
					case T_Enemy:
						_t_enemy_count++;
						break;
					}
				}
			}
		}
	}

	void writelineCollisionCount() const
	{
		if(Debug::getInstance().getDebugScreenIndex() == _writeline_index)
		{
			Debug::getInstance().writeline(_writeline_index, U"Collision Analyzer");
			Debug::getInstance().writeline(_writeline_index, U"T_Block_Count : " + Format(_t_block_count));
			Debug::getInstance().writeline(_writeline_index, U"T_Player_Count : " + Format(_t_player_count));
			Debug::getInstance().writeline(_writeline_index, U"T_Bullet_Count : " + Format(_t_bullet_count));
			Debug::getInstance().writeline(_writeline_index, U"T_Enemy_Count : " + Format(_t_enemy_count));
			Debug::getInstance().writeline(_writeline_index);
		}
	}
};

CollisionManager::CollisionManager() : p_impl(std::make_shared<Impl>())
{
}

void CollisionManager::init()
{
	p_impl->_ptr_entity_list = std::make_shared<std::vector<std::shared_ptr<ICollidable>>>();
}

void CollisionManager::update(double delta_time)
{
	p_impl->checkEntityWithEntity();
	p_impl->analyzeCollision(delta_time);
	p_impl->writelineCollisionCount();
}

void CollisionManager::draw() const
{
}

void CollisionManager::addICollidable(const std::shared_ptr<ICollidable>& ptr_icollidable) const
{
	p_impl->_ptr_entity_list->push_back(ptr_icollidable);
}

void CollisionManager::removeICollidable(const std::shared_ptr<ICollidable>& ptr_icollidable)
{
	auto collidable_it = std::find(p_impl->_ptr_entity_list->begin(), p_impl->_ptr_entity_list->end(),
	                               ptr_icollidable);

	if (collidable_it != p_impl->_ptr_entity_list->end())
	{
		p_impl->_ptr_entity_list->erase(collidable_it);
	}
}

std::shared_ptr<std::vector<std::shared_ptr<ICollidable>>> CollisionManager::getPtrICollisionList()
{
	return p_impl->_ptr_entity_list;
}
