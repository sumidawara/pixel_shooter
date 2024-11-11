#pragma once
#include "Enum.h"

class GameSceneGUIManager
{
public:
	GameSceneGUIManager();
	void init();
	void update(double delta_time);
	void draw();

	//GUIの入力はすべてこのクラスを経由する
	void onAbilitySelectTileClicked(int32 index);
	void onResumeBtnClicked();
	void onSettingBtnClicked();
	void onTitleBtnClicked();
	void onMenuBtnClicked();

	void setIsAbilitySelectEnabled(bool value);
	void setTransitionState(GameSceneTransitionType::State state);

	bool getIsAbilitySelectEnabled() const;
	double getAbilitySelectBlockPopupInterpolationT() const;
	bool getIsGameSceneMenuEnabled() const;
	bool getIsInputLock() const;
	GameSceneTransitionType::State getTransitionState() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
