#include "stdafx.h"
#include "TimeLimitGUI.h"

#include "AssetKey.h"
#include "DebugSetting.h"
#include "God.h"

struct TimeLimitGUI::Impl
{
	Vec2 _pos;
};

TimeLimitGUI::TimeLimitGUI() : p_impl(std::make_shared<Impl>())
{
}

void TimeLimitGUI::init()
{
	p_impl->_pos = {1400, 70};
}

void TimeLimitGUI::update(double delta_time)
{
}

void TimeLimitGUI::draw() const
{
	auto pos = p_impl->_pos;
	auto padding = Vec2{10, 10};
	auto rect = RectF{pos - padding, Vec2{280, 60} + padding * 2};
	double rect_frame_thickness = 5;

	auto text_pos = pos + Vec2{0, 30};
	auto text_num = pos + Vec2{150, 0};
	auto text2_pos = pos + Vec2{250, 30};

	auto time_limit = God::getInstance().getTimeLimitManager()->getTimeLimitInt();
	auto str_text = U"残り時間";
	auto str_num = Format(time_limit);
	auto str_text2 = U"秒";

	rect.draw(Palette::Black).drawFrame(rect_frame_thickness, Palette::White);
	auto rect_text = FontAsset(AssetKey::pixel_b30)(str_text).draw(text_pos);
	auto rect_num = FontAsset(AssetKey::pixel_b60)(str_num).draw(text_num);
	auto rect_text2 = FontAsset(AssetKey::pixel_b30)(str_text2).draw(text2_pos);

	if (DebugSetting::getIsGuiDebuggingVisible())
	{
		rect.draw(DebugSetting::getGuiDebugColor());
		rect_text.draw(DebugSetting::getGuiDebugColor());
		rect_num.draw(DebugSetting::getGuiDebugColor());
		rect_text2.draw(DebugSetting::getGuiDebugColor());
	}
}
