#include "stdafx.h"
#include "GameoverSceneGUIManager.h"

#include "God.h"

struct GameoverSceneGUIManager::Impl
{

};

GameoverSceneGUIManager::GameoverSceneGUIManager() : p_impl(std::make_shared<Impl>())
{
}

void GameoverSceneGUIManager::init()
{
}

void GameoverSceneGUIManager::update(double delta_time)
{
}

void GameoverSceneGUIManager::draw() const
{
}

//イベント

void GameoverSceneGUIManager::onRestartBtnClicked()
{
	God::getInstance().setChangeSceneFlag(Sc_Game);
}

void GameoverSceneGUIManager::onTitleBtnClicked()
{
	God::getInstance().setChangeSceneFlag(Sc_Title);
}
