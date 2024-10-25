#include "stdafx.h"
#include "CollisionAnalyzer.h"
#include "God.h"

struct CollisionAnalyzer::Impl
{
    int32 _t_block_count = 0;
    int32 _t_player_count = 0;
    int32 _t_bullet_count = 0;
    int32 _t_enemy_count = 0;


    double _accumulated_time = 0.0;
    double ANALYZE_INTERVAL = 1.0;

    void count(double time_delta)
    {
        _accumulated_time += time_delta;

        if (ANALYZE_INTERVAL < _accumulated_time)
        {
            _accumulated_time -= ANALYZE_INTERVAL;

            _t_block_count = 0;
            _t_player_count = 0;
            _t_bullet_count = 0;
            _t_enemy_count = 0;

            auto ptr_collision_manager = God::getInstance().getPtrCollisionManager();
        	auto ptr_icollidable_list = ptr_collision_manager->getPtrICollisionList();
            for (int32 i = 0; i < ptr_icollidable_list->size(); i++)
            {
                //ICollidableの数の確認
                switch ((*ptr_icollidable_list)[i]->getType())
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

    void showResult() const
    {
        Print << U"Collision Analyzer";
        Print << U"T_Block_Count : " << _t_block_count;
        Print << U"T_Player_Count : " << _t_player_count;
        Print << U"T_Bullet_Count : " << _t_bullet_count;
        Print << U"T_Enemy_Count : " << _t_enemy_count;
    }
};

CollisionAnalyzer::CollisionAnalyzer() : p_impl(std::make_shared<Impl>())
{

}

void CollisionAnalyzer::init()
{
}

void CollisionAnalyzer::setTBlockCount(const int32 value)
{
	p_impl->_t_block_count = value;
}

void CollisionAnalyzer::setTPlayerCount(const int32 value)
{
	p_impl->_t_player_count = value;
}

void CollisionAnalyzer::setTBulletCount(const int32 value)
{
	p_impl->_t_bullet_count = value;
}

void CollisionAnalyzer::setTEnemyCount(const int32 value)
{
	p_impl->_t_enemy_count = value;
}

int32 CollisionAnalyzer::getTBlockCount() const {
	return p_impl->_t_block_count;
}

int32 CollisionAnalyzer::getTPlayerCount() const {
	return p_impl->_t_player_count;
}

int32 CollisionAnalyzer::getTBulletCount() const {
	return p_impl->_t_bullet_count;
}

int32 CollisionAnalyzer::getTEnemyCount() const {
	return p_impl->_t_enemy_count;
}

void CollisionAnalyzer::draw() const
{
    p_impl->showResult();
}

void CollisionAnalyzer::update(double time_delta)
{
    p_impl->count(time_delta);
}
