#include "stdafx.h"
#include "TitleSceneGUI.h"

#include "TitleSceneMenu.h"

struct TitleSceneGUI::Impl
{
	TitleSceneMenu _titlescene_menu;
};

TitleSceneGUI::TitleSceneGUI() : p_impl(std::make_shared<Impl>())
{
}

void TitleSceneGUI::init()
{
	p_impl->_titlescene_menu.init();
}

void TitleSceneGUI::update(double delta_time)
{
	p_impl->_titlescene_menu.update(delta_time);
}

void TitleSceneGUI::draw() const
{
	p_impl->_titlescene_menu.draw();
}
