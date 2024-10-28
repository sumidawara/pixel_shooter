#include "stdafx.h"
#include "GameoverScene.h"

#include "Debug.h"
#include "GameoverSceneGUI.h"
#include "GameoverSceneGUIManager.h"
#include "God.h"

struct GameoverScene::Impl
{
	std::shared_ptr<GameoverSceneGUI> _gameover_scene_gui;
	std::shared_ptr<GameoverSceneGUIManager> _gameover_scene_gui_manager;

	RenderTexture _render_texture{ Scene::Size() };
};

GameoverScene::GameoverScene(const InitData& init_data)
: IScene (init_data), p_impl(std::make_shared<Impl>())
{
	init();
}

void GameoverScene::init()
{
	p_impl->_gameover_scene_gui = std::make_shared<GameoverSceneGUI>();
	p_impl->_gameover_scene_gui_manager = std::make_shared<GameoverSceneGUIManager>();

	p_impl->_gameover_scene_gui->init();
	p_impl->_gameover_scene_gui_manager->init();

	God::getInstance().setGameoverSceneGUIManager(p_impl->_gameover_scene_gui_manager);
}

void GameoverScene::update()
{
	double delta_time = Scene::DeltaTime();

	p_impl->_gameover_scene_gui->update(delta_time);
	p_impl->_gameover_scene_gui_manager->update(delta_time);
	Debug::getInstance().update(delta_time);

	if(God::getInstance().getSceneTransitionData() == Sc_Game)
	{
		changeScene(Sc_Game, 1000);
	}
	if(God::getInstance().getSceneTransitionData() == Sc_Title)
	{
		changeScene(Sc_Title, 1000);
	}
}

void GameoverScene::draw() const
{
	ClearPrint();
	{
		const ScopedRenderTarget2D target{ p_impl->_render_texture.clear(Palette::Black) };

		p_impl->_gameover_scene_gui->draw();
		Debug::getInstance().draw();
	}
	p_impl->_render_texture.draw();
}

void GameoverScene::drawFadeIn(double t) const
{
	Vec2 pos = {0, 0};
	Vec2 size = { (1 - t) * Scene::Size().x, Scene::Size().y};
	RectF fade_in_background = {pos, size};

	draw();
	fade_in_background.draw(Palette::Black);
}

void GameoverScene::drawFadeOut(double t) const
{
	Vec2 pos = {0, 0};
	Vec2 size = { t * Scene::Size().x, Scene::Size().y};
	RectF fade_in_background = {pos, size};

	draw();
	fade_in_background.draw(Palette::Black);
}
