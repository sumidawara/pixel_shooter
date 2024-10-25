#include "stdafx.h"
#include "GameoverSceneGUI.h"

#include "GameoverMenu.h"

struct GameoverSceneGUI::Impl
{
	GameoverMenu _gameover_menu;
};

GameoverSceneGUI::GameoverSceneGUI() : p_impl(std::make_shared<Impl>())
{
}

void GameoverSceneGUI::init()
{
	p_impl->_gameover_menu.init();
}

void GameoverSceneGUI::update(double delta_time)
{
	p_impl->_gameover_menu.update(delta_time);
}

void GameoverSceneGUI::draw() const
{
	p_impl->_gameover_menu.draw();
}
