#include "stdafx.h"
#include "GameSceneGUI.h"

#include "GameSceneMenu.h"
#include "AbilitySelectBlock/AbilitySelectBlock.h"
#include "StatusBar/StatusBar.h"
#include "God.h"
#include "AbilitySummary/AbilitySummary.h"
#include "GameSceneTransition/GameSceneTransition.h"

struct GameSceneGUI::Impl
{
	StatusBar _status_bar;
	AbilitySelectBlock _ability_select_block;
	AbilitySummary _ability_summary;
	GameSceneMenu _gamescene_menu;
	GameSceneTransition _gamescene_transition;

};

GameSceneGUI::GameSceneGUI() : p_impl(std::make_shared<Impl>())
{
}

void GameSceneGUI::init()
{
	p_impl->_status_bar.init({0, 900});
	p_impl->_ability_select_block.init();
	p_impl->_ability_summary.init(Vec2{100, 100});
	p_impl->_gamescene_menu.init();
	p_impl->_gamescene_transition.init(1.0, 1.0);
}

void GameSceneGUI::update(double delta_time)
{
	auto _ptr_gamescene_gui_manager = God::getInstance().getPtrGameSceneGUIManager();
	auto is_ability_select_enabled = _ptr_gamescene_gui_manager->getIsAbilitySelectEnabled();
	auto is_gamescene_menu_enabled = _ptr_gamescene_gui_manager->getIsGameSceneMenuEnabled();

	p_impl->_status_bar.update(delta_time);
	p_impl->_ability_summary.update(delta_time);

	if(is_ability_select_enabled)
	{
		p_impl->_ability_select_block.update(delta_time);
	}
	if(is_gamescene_menu_enabled)
	{
		p_impl->_gamescene_menu.update(delta_time);
	}

	p_impl->_gamescene_transition.update(delta_time);
}

void GameSceneGUI::draw() const
{
	auto _ptr_gamescene_gui_manager = God::getInstance().getPtrGameSceneGUIManager();
	auto is_ability_select_enabled = _ptr_gamescene_gui_manager->getIsAbilitySelectEnabled();
	auto is_gamescene_menu_enabled = _ptr_gamescene_gui_manager->getIsGameSceneMenuEnabled();

	p_impl->_status_bar.draw();
	p_impl->_ability_summary.draw();


	if(is_ability_select_enabled)
	{
		p_impl->_ability_select_block.draw();
	}
	if(is_gamescene_menu_enabled)
	{
		p_impl->_gamescene_menu.draw();
	}

	p_impl->_gamescene_transition.draw();
}
