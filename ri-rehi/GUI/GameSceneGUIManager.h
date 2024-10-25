#pragma once

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

	void setIsAbilitySelectEnabled(bool value);

	bool getIsAbilitySelectEnabled() const;
	bool getIsGameSceneMenuEnabled() const;
	bool getIsInputLock() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
