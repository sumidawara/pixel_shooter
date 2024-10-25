#include "stdafx.h"
#include "GameSceneGUI.h"

#include "GameSceneMenu.h"
#include "AbilitySelectBlock/AbilitySelectBlock.h"
#include "StatusBar/StatusBar.h"
#include "God.h"

struct GameSceneGUI::Impl
{
	StatusBar _status_bar;
	AbilitySelectBlock _ability_select_block;
	GameSceneMenu _gamescene_menu;

};

GameSceneGUI::GameSceneGUI() : p_impl(std::make_shared<Impl>())
{
}

void GameSceneGUI::init()
{
	p_impl->_status_bar.init({0, 900});
	p_impl->_ability_select_block.init({260, 200});
	p_impl->_gamescene_menu.init();
}

void GameSceneGUI::update(double delta_time)
{
	auto _ptr_gamescene_gui_manager = God::getInstance().getPtrGameSceneGUIManager();
	auto is_ability_select_enabled = _ptr_gamescene_gui_manager->getIsAbilitySelectEnabled();
	auto is_gamescene_menu_enabled = _ptr_gamescene_gui_manager->getIsGameSceneMenuEnabled();

	p_impl->_status_bar.update(delta_time);
	if(is_ability_select_enabled)
	{
		p_impl->_ability_select_block.update(delta_time);
	}
	if(is_gamescene_menu_enabled)
	{
		p_impl->_gamescene_menu.update(delta_time);
	}
}

void GameSceneGUI::draw() const
{
	auto _ptr_gamescene_gui_manager = God::getInstance().getPtrGameSceneGUIManager();
	auto is_ability_select_enabled = _ptr_gamescene_gui_manager->getIsAbilitySelectEnabled();
	auto is_gamescene_menu_enabled = _ptr_gamescene_gui_manager->getIsGameSceneMenuEnabled();

	p_impl->_status_bar.draw();

	if(is_ability_select_enabled)
	{
		p_impl->_ability_select_block.draw();
	}
	if(is_gamescene_menu_enabled)
	{
		p_impl->_gamescene_menu.draw();
	}
}
