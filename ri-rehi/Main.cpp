#pragma once
#include <Siv3D.hpp> // OpenSiv3D v0.6.3

#include "AssetManager.h"
#include "Player/Player.h"
#include "DebugSetting.h"
#include "GameoverScene/GameoverScene.h"

#include "GameScene.h"
#include "GameClearScene/GameClearScene.h"
#include "TitleScene/TitleScene.h"


void Main()
{
	Window::Resize(1920, 1080);
	Window::SetStyle(WindowStyle::Sizable);

	Scene::SetTextureFilter(TextureFilter::Nearest);
	Scene::SetResizeMode(ResizeMode::Keep);

	//System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	// RenderTextureを拡大描画時にぼやけないように：
	const ScopedRenderStates2D state(SamplerState::ClampNearest);

	Scene::SetBackground(Palette::Pink);

    FileSystem::ChangeCurrentDirectory( U"C:/Users/mrkei/root/development/C++/siv3d/ri-rehi/ri-rehi/App");
    
	AssetManager::registerAsset();
	Debug::getInstance().init();

	App manager;
	manager.add<GameScene>(Sc_Game);
	manager.add<GameoverScene>(Sc_Gameover);
    manager.add<GameClearScene>(Sc_GameClear);
	manager.add<TitleScene>(Sc_Title);

	manager.init(Sc_Game, 500);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
