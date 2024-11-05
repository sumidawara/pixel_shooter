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

					if (not rectf_i.intersects(rectf_j)) continue;

					ptr_icollidable_i->onCollision(*ptr_icollidable_j);
					ptr_icollidable_j->onCollision(*ptr_icollidable_i);
				}
			}
		}
	}

	void checkEntityWithBlock()
	{
		//4頂点の取得
		for (int32 i = 0; i < _ptr_entity_list->size(); i++)
		{
			auto ptr_entity_i = _ptr_entity_list->at(i);
			auto rect = ptr_entity_i->getBoundingShape();
			auto world = God::getInstance().getWorld();

			std::vector<Point> four_points;
			four_points.push_back(world.worldPos2indexPos(rect.tl()));
			four_points.push_back(world.worldPos2indexPos(rect.tr()));
			four_points.push_back(world.worldPos2indexPos(rect.bl()));
			four_points.push_back(world.worldPos2indexPos(rect.br()));

			auto collidable_block_grid = world.getCollidableBlockGrid();
			std::vector<std::shared_ptr<ICollidable>> buffer;//casted_ptr_blockを格納
			for(int j = 0; j < 4; j++)
			{
				if(world.isBlockAtIndexPos(four_points[j]))
				{
					//４頂点のインデックス座標上に存在するblockのポインタを取得
					auto ptr_block = collidable_block_grid->at(four_points[j].y, four_points[j].x);
					auto casted_ptr_block = std::static_pointer_cast<ICollidable>(ptr_block);

					if (std::find(buffer.begin(), buffer.end(), casted_ptr_block) != buffer.end())
					{
						//以前に衝突判定したものと同一のブロック
					}
					else
					{
						//以前に衝突判定したものとは異なるブロック

						casted_ptr_block->onCollision(*ptr_entity_i);
						ptr_entity_i->onCollision(*casted_ptr_block);

						buffer.push_back(casted_ptr_block);
					}
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
	p_impl->checkEntityWithBlock();
	p_impl->analyzeCollision(delta_time);
	p_impl->writelineCollisionCount();
}

void CollisionManager::draw() const
{
}

void CollisionManager::clear()
{
	p_impl->_ptr_entity_list->clear();
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
