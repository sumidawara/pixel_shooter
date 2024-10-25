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

void TitleSceneGUIManager::onStarBtnClicked()
{
	God::getInstance().setChangeSceneFlag(Sc_Game);
}

void TitleSceneGUIManager::onSettingBtnClicked()
{
}

void TitleSceneGUIManager::onExitBtnClicked()
{
	System::Exit();
}
