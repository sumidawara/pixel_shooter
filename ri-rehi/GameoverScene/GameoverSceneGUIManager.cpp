﻿#include "stdafx.h"
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
	//ステージ数を初期化
	God::getInstance().setStageNum(1);

	God::getInstance().setSceneTransitionData(SceneTransitionData::Game());
}

void GameoverSceneGUIManager::onTitleBtnClicked()
{
	God::getInstance().setSceneTransitionData(SceneTransitionData::Title());
}
