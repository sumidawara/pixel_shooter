﻿#include "stdafx.h"
#include "GameoverSceneGUI.h"

#include "AssetKey.h"
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
	FontAsset(AssetKey::pixel_b80)(U"GAME OVER").drawAt(Scene::Width() / 2, 310);
	p_impl->_gameover_menu.draw();
}
