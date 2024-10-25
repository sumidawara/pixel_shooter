#pragma once

class GameoverSceneGUIManager
{
public:
	GameoverSceneGUIManager();
	void init();
	void update(double delta_time);
	void draw() const;

	void onRestartBtnClicked();
	void onTitleBtnClicked();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
