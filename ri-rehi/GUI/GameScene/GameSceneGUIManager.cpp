#include "stdafx.h"
#include "GameSceneGUIManager.h"

#include "Debug.h"
#include "God.h"

struct GameSceneGUIManager::Impl
{
	bool _is_ability_select_block_enabled = false;

	bool _is_gamescene_menu_enabled = false;

	//誤入力防止
	bool _is_inputlock = false;
	double _accumulated_inputlock_time = 0.0;
	double _threshold_inputlock_time = 0.4;

	void input()
	{
		//Menu表示
		if(KeyP.down())
		{
			setIsGamesceneMenuEnabled(not _is_gamescene_menu_enabled);
		}
	}

	void setIsGamesceneMenuEnabled(int value)
	{
		_is_gamescene_menu_enabled = value;
		God::getInstance().getPtrTimeManager()->setIsManuallyPaused(value);
	}

	void updateInputLock(double delta_time)
	{
		_accumulated_inputlock_time += delta_time;

		if(_threshold_inputlock_time < _accumulated_inputlock_time)
		{
			_accumulated_inputlock_time = 0;
			_is_inputlock = false;
		}
	}
};

GameSceneGUIManager::GameSceneGUIManager() : p_impl(std::make_shared<Impl>())
{
}

void GameSceneGUIManager::init()
{
}

void GameSceneGUIManager::update(double delta_time)
{
	p_impl->input();
	if(p_impl->_is_inputlock) p_impl->updateInputLock(delta_time);

}

void GameSceneGUIManager::draw()
{
}


//イベント

void GameSceneGUIManager::onAbilitySelectTileClicked(int32 index)
{
	God::getInstance().getPtrAbilityManager()->addAbility(index);

	God::getInstance().getPtrTimeManager()->setIsForciblyPaused(false);
	p_impl->_is_ability_select_block_enabled = false;
}

void GameSceneGUIManager::onResumeBtnClicked()
{
	p_impl->setIsGamesceneMenuEnabled(false);
}

void GameSceneGUIManager::onSettingBtnClicked()
{
}

void GameSceneGUIManager::onTitleBtnClicked()
{
	God::getInstance().setSceneTransitionData(SceneTransitionData::Title());
}

//セッター

void GameSceneGUIManager::setIsAbilitySelectEnabled(bool value)
{
	//誤入力を防ぐためにしばらくの間は入力禁止
	if(value) p_impl->_is_inputlock = true;

	p_impl->_is_ability_select_block_enabled = value;
}

//ゲッター

bool GameSceneGUIManager::getIsAbilitySelectEnabled() const
{
	return p_impl->_is_ability_select_block_enabled;
}

bool GameSceneGUIManager::getIsGameSceneMenuEnabled() const
{
	return p_impl->_is_gamescene_menu_enabled;
}

bool GameSceneGUIManager::getIsInputLock() const
{
	return p_impl->_is_inputlock;
}
