#include "stdafx.h"
#include "TitleSceneGUIManager.h"

#include "God.h"
#include "TitleGod.h"

struct TitleSceneGUIManager::Impl
{

};

TitleSceneGUIManager::TitleSceneGUIManager() : p_impl(std::make_shared<Impl>())
{
}

void TitleSceneGUIManager::init()
{
}

void TitleSceneGUIManager::update(double delta_time)
{
}

void TitleSceneGUIManager::draw() const
{
}

//イベント

void TitleSceneGUIManager::onStartBtnClicked()
{
	//ステージ数を初期化
	God::getInstance().setStageNum(1);

	God::getInstance().setSceneTransitionData(SceneTransitionData::Game());
}

void TitleSceneGUIManager::onSettingBtnClicked()
{
}

void TitleSceneGUIManager::onExitBtnClicked()
{
	System::Exit();
}
