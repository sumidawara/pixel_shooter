#pragma once
#include "Enum.h"
#include "TitleSceneGUIManager.h"

class TitleGod
{
public:
	TitleGod(const TitleGod&) = delete;
	TitleGod& operator=(const TitleGod&) = delete;
	TitleGod(TitleGod&&) = delete;
	TitleGod& operator=(TitleGod&&) = delete;

	static TitleGod& getInstance();

	std::shared_ptr<TitleSceneGUIManager> getTitleSceneGUIManager() const;
	SceneType getChangeSceneFlag() const;

	void setTitleSceneGUIManager(const std::shared_ptr<TitleSceneGUIManager>& value);
	void setChangeSceneFlag(SceneType value);

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;

	TitleGod();
	~TitleGod() = default;
};
