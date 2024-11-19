#pragma once
#include "Enum.h"

class SceneTransitionData
{
public:
	SceneTransitionData();
	void init(SceneType destination_scene_type, int32 transition_time_millisecond, bool is_gamescene_to_gamescene);

	SceneType getDestinationSceneType() const;
	int32 getTransitionTimeMillisecond() const;
	bool getIsGameSceneToGameScene() const;

	void setIsGameSceneToGameScene(bool value);

	static SceneTransitionData None();
	static SceneTransitionData Game();
	static SceneTransitionData GameOver();
	static SceneTransitionData Title();
    static SceneTransitionData GameClear();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
