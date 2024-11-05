#pragma once

class TitleSceneGUIManager
{
public:
	TitleSceneGUIManager();
	void init();
	void update(double delta_time);
	void draw() const;

	void onStartBtnClicked();
	void onSettingBtnClicked();
	void onExitBtnClicked();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
