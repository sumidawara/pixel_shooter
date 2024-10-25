#pragma once
#include <Siv3D.hpp> // OpenSiv3D v0.6.3
#include "Player/Player.h"
#include "DebugSetting.h"
#include "Scene/GameoverScene.h"

#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"


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

	FileSystem::ChangeCurrentDirectory( U"E:/root/development/c++/siv3d/vanpire_survival_like_game_1/vanpire_survival_like_game_1/App");
	FileSystem::ChangeCurrentDirectory( U"C:/Users/mrkei/root/development/C++/siv3d/vampire_survival_like_game/vanpire_survival_like_game_1/App");

	App manager;
	manager.add<GameScene>(Sc_Game);
	manager.add<GameoverScene>(Sc_Gameover);
	manager.add<TitleScene>(Sc_Title);

	manager.init(Sc_Game, 0.0);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
