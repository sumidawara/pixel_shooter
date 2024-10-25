#include "stdafx.h"
#include "TitleGod.h"

#include "Enum.h"

struct TitleGod::Impl
{
	std::shared_ptr<TitleSceneGUIManager> _ptr_titlescene_gui_manager;
	SceneType _change_scene_flag;
};

TitleGod::TitleGod() : p_impl(std::make_shared<Impl>())
{
}

TitleGod& TitleGod::getInstance()
{
	static TitleGod instance;
	return instance;
}

//ゲッター

std::shared_ptr<TitleSceneGUIManager> TitleGod::getTitleSceneGUIManager() const
{
	return p_impl->_ptr_titlescene_gui_manager;
}

SceneType TitleGod::getChangeSceneFlag() const
{
	return p_impl->_change_scene_flag;
}

//セッター

void TitleGod::setTitleSceneGUIManager(const std::shared_ptr<TitleSceneGUIManager>& value)
{
	p_impl->_ptr_titlescene_gui_manager = value;
}

void TitleGod::setChangeSceneFlag(SceneType value)
{
	p_impl->_change_scene_flag = value;
}
