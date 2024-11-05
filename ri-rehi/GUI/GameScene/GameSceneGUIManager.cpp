﻿#include "stdafx.h"
#include "GameSceneGUIManager.h"
#include "Enum.h"

#include "Debug.h"
#include "God.h"
#include "GameSceneTransition/GameSceneTransition.h"

struct GameSceneGUIManager::Impl
{
	bool _is_ability_select_block_enabled = false;

	bool _is_gamescene_menu_enabled = false;

	GameSceneTransitionType::State _transition_state = GameSceneTransitionType::State::None;

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

	//トランジションがフェードイン
	void onEnterTransitionStarting()
	{
		Debug::getInstance().writeline(0, U"GameSceneTransition : Enter Starting");
	}

	//トランジションがフェードアウト
	void onEnterTransitionEnding()
	{
		Debug::getInstance().writeline(0, U"GameSceneTransition : Enter Ending");

		auto next_stage_num = God::getInstance().getStageNum() + 1;
		God::getInstance().setStageNum(next_stage_num);

		auto transition_data = SceneTransitionData::Game();
		transition_data.setIsGameSceneToGameScene(true);
		God::getInstance().setSceneTransitionData(transition_data);
	}

	//トランジションが完全に終了
	void onEnterTransitionNone()
	{
		Debug::getInstance().writeline(0, U"GameSceneTransition : Enter None");
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

void GameSceneGUIManager::setTransitionState(GameSceneTransitionType::State state)
{
	p_impl->_transition_state = state;

	switch (p_impl->_transition_state)
	{
	case GameSceneTransitionType::Starting:
		p_impl->onEnterTransitionStarting();
		break;
	case GameSceneTransitionType::Ending:
		p_impl->onEnterTransitionEnding();
		break;
	case GameSceneTransitionType::None:
		p_impl->onEnterTransitionNone();
		break;
	}
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

GameSceneTransitionType::State GameSceneGUIManager::getTransitionState() const
{
	return p_impl->_transition_state;
}
