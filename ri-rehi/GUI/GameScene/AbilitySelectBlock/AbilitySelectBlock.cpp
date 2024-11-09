#include "stdafx.h"
#include "AbilitySelectBlock.h"

#include "AbilitySelectTile.h"
#include "AssetKey.h"
#include "God.h"
#include "MathEx.h"

struct AbilitySelectBlock::Impl
{
	Vec2 _pos;
	Vec2 _start_pos = {260, -1200};
	Vec2 _end_pos = {260, 200};

	Vec2 _text_pos;
	Vec2 _text_pos_relative = {0, -100};

	std::vector<AbilitySelectTile> _ability_select_tile_list;
	int32 TILE_COUNT = 3;
	double TILE_INTERVAL = 500;

	RectF _back_ground = {Vec2{0, 0}, Scene::Size()};
	ColorF _back_ground_colorf;
	double _start_alpha = 0.0;
	double _end_alpha = 0.6;

	void updatePos()
	{
		auto t = God::getInstance().getPtrGameSceneGUIManager()->getAbilitySelectBlockPopupInterpolationT();
		auto e = EaseOut(Easing::Quad, t);
		_pos = MathEx::lerp(_start_pos, _end_pos, e);
		_text_pos = _pos + _text_pos_relative;

		for(int32 i = 0; i < TILE_COUNT; i++)
		{
			auto p = _pos + Vec2{TILE_INTERVAL * i, 0};
			_ability_select_tile_list[i].setPos(p);
		}
	}

	void updateBackGroundColor()
	{
		auto t = God::getInstance().getPtrGameSceneGUIManager()->getAbilitySelectBlockPopupInterpolationT();

		_back_ground_colorf = ColorF{0, 0, 0, std::lerp(_start_alpha, _end_alpha, t)};
	}
};

AbilitySelectBlock::AbilitySelectBlock() : p_impl(std::make_shared<Impl>())
{
}

void AbilitySelectBlock::init()
{
	p_impl->_pos = p_impl->_start_pos;
	p_impl->_text_pos = p_impl->_pos + p_impl->_text_pos_relative;

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
	p_impl->updatePos();
	p_impl->updateBackGroundColor();

	//それぞれのタイルの更新
	for(int32 i = 0; i < p_impl->TILE_COUNT; i++)
	{
		p_impl->_ability_select_tile_list[i].update(delta_time);
	}
}

void AbilitySelectBlock::draw()
{
	p_impl->_back_ground.draw(p_impl->_back_ground_colorf);

	FontAsset(AssetKey::pixel_b60)(U"LEVEL UP").drawAt(p_impl->_text_pos, GraphicSetting::getPINK());

	for(int32 i = 0; i < p_impl->TILE_COUNT; i++)
	{
		p_impl->_ability_select_tile_list[i].draw();
	}
}
