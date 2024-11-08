#include "stdafx.h"
#include "AbilitySelectBlock.h"

#include "AbilitySelectTile.h"
#include "God.h"

struct AbilitySelectBlock::Impl
{
	Vec2 _pos;

	std::vector<AbilitySelectTile> _ability_select_tile_list;
	int32 TILE_COUNT = 3;
	double TILE_INTERVAL = 500;

	void updatePos()
	{
		_pos = God::getInstance().getPtrGameSceneGUIManager()->getAbilitySelectBlockPos();

		_ability_select_tile_list.resize(TILE_COUNT);
		for(int32 i = 0; i < TILE_COUNT; i++)
		{
			auto p = _pos + Vec2{TILE_INTERVAL * i, 0};
			_ability_select_tile_list[i].setPos(p);
		}
	}
};

AbilitySelectBlock::AbilitySelectBlock() : p_impl(std::make_shared<Impl>())
{
}

void AbilitySelectBlock::init()
{
	//見えない所で初期化すればどこでもいい（はず）
	p_impl->_pos = {260, -1200};

	int32 TILE_COUNT = p_impl->TILE_COUNT;
	double TILE_INTERVAL = p_impl->TILE_INTERVAL;

	p_impl->_ability_select_tile_list.resize(TILE_COUNT);
	for(int32 i = 0; i < TILE_COUNT; i++)
	{
		auto p = p_impl->_pos + Vec2{TILE_INTERVAL * i, 0};
		p_impl->_ability_select_tile_list[i].init(p, i);
	}
}

void AbilitySelectBlock::update(double delta_time)
{
	//位置情報の更新
	p_impl->updatePos();

	//それぞれのタイルの更新
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
