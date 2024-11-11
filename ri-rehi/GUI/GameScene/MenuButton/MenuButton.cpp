#include "stdafx.h"
#include "MenuButton.h"

#include "God.h"
#include "GraphicSetting.h"

struct MenuButton::Impl
{
	RectF _rect = {Vec2{50, 50}, Vec2{50, 50}};

	double _thickness = 5;
};

MenuButton::MenuButton() : p_impl(std::make_shared<Impl>())
{
}

void MenuButton::init()
{

}

void MenuButton::update(double delta_time)
{
	if(p_impl->_rect.leftClicked())
	{
		auto gamescene_gui_manager = God::getInstance().getPtrGameSceneGUIManager();
		gamescene_gui_manager->onMenuBtnClicked();
	}
}

void MenuButton::draw() const
{
	auto pink = GraphicSetting::getPINK();
	if(p_impl->_rect.mouseOver())
	{
		p_impl->_rect.draw(Palette::Black).drawFrame(p_impl->_thickness, pink);
	}
	else
	{
		p_impl->_rect.draw(Palette::Black).drawFrame(p_impl->_thickness, Palette::White);
	}
}
