#include "stdafx.h"
#include "HPBlock.h"

#include "AssetKey.h"
#include "DebugSetting.h"
#include "GraphicSetting.h"
#include "HPBar.h"

struct HPBlock::Impl
{
	Vec2 _pos;
	Vec2 _hptext_pos;
	HPBar _hpbar;
};

HPBlock::HPBlock() : p_impl(std::make_shared<Impl>())
{
}

void HPBlock::init(Vec2 pos)
{
	p_impl->_pos = pos;

	Vec2 hptext_pos = pos + Vec2{0, 0};
	p_impl->_hptext_pos = hptext_pos;

	Vec2 hpbar_pos = pos + Vec2{120, 0};
	Vec2 hpbar_size{ 700, 100 };
	p_impl->_hpbar.init(RectF{hpbar_pos, hpbar_size}, 100, 100);
}

void HPBlock::update(double delta_time)
{
}

void HPBlock::draw() const
{
	bool is_gui_debugging_visible = DebugSetting::getIsGuiDebuggingVisible();
	if(is_gui_debugging_visible) Circle{p_impl->_pos, 3}.draw(DebugSetting::getGuiDebugColor());

	FontAsset(AssetKey::pixel_b80)(U"HP").draw(p_impl->_hptext_pos, GraphicSetting::getPINK());
	if(is_gui_debugging_visible) Circle{p_impl->_hptext_pos, 3}.draw(DebugSetting::getGuiDebugColor());

	p_impl->_hpbar.draw();
	if(is_gui_debugging_visible) Circle{p_impl->_hpbar.getPos(), 3}.draw(DebugSetting::getGuiDebugColor());
}

void HPBlock::setHP(int32 current_hp, int32 max_hpe)
{
	p_impl->_hpbar.setHP(current_hp, max_hpe);
}
