#include "stdafx.h"
#include "Button.h"

#include "DebugSetting.h"
#include "GraphicSetting.h"

struct Button::Impl
{
	RectF _rectf;
	String _text;
	AssetName _font_asset_name;

	ColorF _hovered_color;
	ColorF _normal_color;

	bool _is_mouse_hovered = false;
	bool _is_mouse_clicked = false; //親側が明示的にfalseに再設定してやる必要がある。
};

Button::Button() : p_impl(std::make_shared<Impl>())
{
}

void Button::init(const RectF& rectf, const String& text, const AssetNameView& font_asset_name)
{
	p_impl->_rectf = rectf;
	p_impl->_text = text;
	p_impl->_font_asset_name = font_asset_name;

	p_impl->_hovered_color = GraphicSetting::getPINK();
	p_impl->_normal_color = Palette::White;
}

void Button::update(double delta_time)
{
	if(p_impl->_rectf.mouseOver())
	{
		p_impl->_is_mouse_hovered = true;
	}
	else
	{
		p_impl->_is_mouse_hovered = false;
	}

	if(p_impl->_rectf.leftClicked())
	{
		p_impl->_is_mouse_clicked = true;
	}
}

void Button::draw() const
{
	if(p_impl->_is_mouse_hovered)
	{
		auto hovered_color = p_impl->_hovered_color;
		FontAsset(p_impl->_font_asset_name)(p_impl->_text).drawAt(p_impl->_rectf.center(), hovered_color);
	}
	else
	{
		auto normal_color = p_impl->_normal_color;
		FontAsset(p_impl->_font_asset_name)(p_impl->_text).drawAt(p_impl->_rectf.center(), normal_color);
	}

	if(DebugSetting::getIsGuiDebuggingVisible())
	{
		p_impl->_rectf.draw(DebugSetting::getGuiDebugColor());
	}
}

bool Button::getIsClicked() const
{
	return p_impl->_is_mouse_clicked;
}

bool Button::getIsHovered() const
{
	return p_impl->_is_mouse_hovered;
}

void Button::setIsClicked(bool value)
{
	p_impl->_is_mouse_clicked = value;
}
