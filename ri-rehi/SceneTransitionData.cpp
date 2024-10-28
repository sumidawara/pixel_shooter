#include "stdafx.h"
#include "SceneTransitionData.h"

struct SceneTransitionData::Impl
{
	SceneType _destination_scene_type;
	int32 _transition_time_millisecond;
	bool _is_gamescene_to_gamescene;
};

SceneTransitionData::SceneTransitionData() : p_impl(std::make_shared<Impl>())
{
}

void SceneTransitionData::init(
	SceneType destination_scene_type,int32 transition_time_millisecond,bool is_gamescene_to_gamescene)
{
	p_impl->_destination_scene_type = destination_scene_type;
	p_impl->_transition_time_millisecond = transition_time_millisecond;
	p_impl->_is_gamescene_to_gamescene = is_gamescene_to_gamescene;
}

SceneType SceneTransitionData::getDestinationSceneType() const
{
	return p_impl->_destination_scene_type;
}

int32 SceneTransitionData::getTransitionTimeMillisecond() const
{
	return p_impl->_transition_time_millisecond;
}

bool SceneTransitionData::getIsGameSceneToGameScene() const
{
	return p_impl->_is_gamescene_to_gamescene;
}

void SceneTransitionData::setIsGameSceneToGameScene(bool value)
{
	p_impl->_is_gamescene_to_gamescene = value;
}

SceneTransitionData SceneTransitionData::None()
{
	SceneTransitionData scene_transition_data;
	scene_transition_data.init(Sc_None, -1, false);
	return scene_transition_data;
}

SceneTransitionData SceneTransitionData::Game()
{
	SceneTransitionData scene_transition_data;
	scene_transition_data.init(Sc_Game, 1000, false);
	return scene_transition_data;
}

SceneTransitionData SceneTransitionData::GameOver()
{
	SceneTransitionData scene_transition_data;
	scene_transition_data.init(Sc_Gameover, 1000, false);
	return scene_transition_data;
}

SceneTransitionData SceneTransitionData::Title()
{
	SceneTransitionData scene_transition_data;
	scene_transition_data.init(Sc_Title, 1000, false);
	return scene_transition_data;
}
