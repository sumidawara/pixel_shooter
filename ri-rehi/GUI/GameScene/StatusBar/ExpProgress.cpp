#include "stdafx.h"
#include "ExpProgress.h"

#include "AssetKey.h"
#include "DebugSetting.h"
#include "GraphicSetting.h"

struct ExpProgress::Impl
{
	Vec2 _pos;
	Vec2 _text_tsuginoreberumade_pos;
	Vec2 _text_ato_xx_exp_pos;

	int32 _remaining_exp_to_next_levelup = 1;
};

ExpProgress::ExpProgress() : p_impl(std::make_shared<Impl>())
{
}

void ExpProgress::init(Vec2 pos)
{
	p_impl->_pos = pos;

	Vec2 text_tsuginoreberumade_pos = pos + Vec2{0, 0};
	p_impl->_text_tsuginoreberumade_pos = text_tsuginoreberumade_pos;

	Vec2 text_atoXXexp_pos = pos + Vec2{0, 40};
	p_impl->_text_ato_xx_exp_pos = text_atoXXexp_pos;
}

void ExpProgress::update(double delta_time)
{
}

void ExpProgress::draw() const
{
	bool is_gui_debugging_visible = DebugSetting::getIsGuiDebuggingVisible();
	if(is_gui_debugging_visible) Circle{p_impl->_pos, 3}.draw(DebugSetting::getGuiDebugColor());

	FontAsset(AssetKey::pixel_b24)(U"次のレベルまで").draw(p_impl->_text_tsuginoreberumade_pos, GraphicSetting::getSKY());
	if(is_gui_debugging_visible) Circle{p_impl->_text_tsuginoreberumade_pos, 3}.draw(DebugSetting::getGuiDebugColor());

	String str_ato_xx_exp = U"あと" + Format(p_impl->_remaining_exp_to_next_levelup) + U"exp";
	FontAsset(AssetKey::pixel_b24)(str_ato_xx_exp).draw(p_impl->_text_ato_xx_exp_pos, GraphicSetting::getSKY());
	if(is_gui_debugging_visible) Circle{p_impl->_text_ato_xx_exp_pos, 3}.draw(DebugSetting::getGuiDebugColor());
}

void ExpProgress::setRemainingExpToNextLevelUp(int32 value)
{
	p_impl->_remaining_exp_to_next_levelup = value;
}
