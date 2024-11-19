#include "stdafx.h"
#include "GameClearSceneGUI.h"

#include "AssetKey.h"
#include "GameClearMenu.h"

struct GameClearSceneGUI::Impl
{
    GameClearMenu _gameclear_menu;   
};

GameClearSceneGUI::GameClearSceneGUI() : p_impl(std::make_shared<Impl>())
{
}

void GameClearSceneGUI::init()
{
    p_impl->_gameclear_menu.init();
}

void GameClearSceneGUI::update(double delta_time)
{
    p_impl->_gameclear_menu.update(delta_time);
}

void GameClearSceneGUI::draw() const
{
    FontAsset(AssetKey::pixel_b80)(U"GAME CLEAR").drawAt(Scene::Width() / 2, 310);
    p_impl->_gameclear_menu.draw();
}
