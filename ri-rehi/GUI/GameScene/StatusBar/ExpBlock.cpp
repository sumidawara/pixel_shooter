#include "stdafx.h"
#include "ExpBlock.h"
#include "DebugSetting.h"

struct ExpBlock::Impl
{
	Vec2 _pos;
	Vec2 _level_text_pos;
	ExpProgress _expprogress;

	int32 _level = 1;
};

ExpBlock::ExpBlock() : p_impl(std::make_shared<Impl>())
{
}

void ExpBlock::init(Vec2 pos)
{
	p_impl->_pos = pos;

	Vec2 level_text_pos = pos +  Vec2{0, 0};
	p_impl->_level_text_pos = level_text_pos;

	Vec2 expprogress_pos = pos + Vec2{160, 10};
	p_impl->_expprogress.init(expprogress_pos);
}

void ExpBlock::update(double delta_time)
{

}

void ExpBlock::draw() const
{
	bool is_gui_debugging_visible = DebugSetting::getIsGuiDebuggingVisible();
	if(is_gui_debugging_visible) Circle{p_impl->_pos, 3}.draw(DebugSetting::getGuiDebugColor());

	String str_lv_xx = U"Lv" + Format(p_impl->_level);
	FontAsset(U"pixel_b80")(str_lv_xx).draw(p_impl->_level_text_pos);
	if(is_gui_debugging_visible) Circle{p_impl->_level_text_pos, 3}.draw(DebugSetting::getGuiDebugColor());

	p_impl->_expprogress.draw();
}

void ExpBlock::setLevel(int32 value)
{
	p_impl->_level = value;
}

void ExpBlock::setRemainingExpToNextLevelUp(int32 value)
{
	p_impl->_expprogress.setRemainingExpToNextLevelUp(value);
}
