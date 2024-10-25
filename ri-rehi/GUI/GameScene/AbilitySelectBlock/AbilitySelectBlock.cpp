#include "stdafx.h"
#include "AbilitySelectBlock.h"

#include "AbilitySelectTile.h"
#include "God.h"

struct AbilitySelectBlock::Impl
{
	Vec2 _pos;

	std::vector<AbilitySelectTile> _ability_select_tile_list;
	int32 TILE_COUNT = 3;
};

AbilitySelectBlock::AbilitySelectBlock() : p_impl(std::make_shared<Impl>())
{
}

void AbilitySelectBlock::init(Vec2 pos)
{
	p_impl->_pos = pos;

	int32 TILE_COUNT = p_impl->TILE_COUNT;
	double TILE_INTERVAL = 500;

	p_impl->_ability_select_tile_list.resize(TILE_COUNT);
	for(int32 i = 0; i < TILE_COUNT; i++)
	{
		auto p = pos + Vec2{TILE_INTERVAL * i, 0};
		p_impl->_ability_select_tile_list[i].init(p, i);
	}
}

void AbilitySelectBlock::update(double delta_time)
{
	for(int32 i = 0; i < p_impl->TILE_COUNT; i++)
	{
		p_impl->_ability_select_tile_list[i].update(delta_time);
	}
}

void AbilitySelectBlock::draw()
{
	for(int32 i = 0; i < p_impl->TILE_COUNT; i++)
	{
		p_impl->_ability_select_tile_list[i].draw();
	}
}
