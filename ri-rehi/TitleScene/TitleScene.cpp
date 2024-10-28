#include "stdafx.h"
#include "TitleScene.h"

#include "Debug.h"
#include "God.h"
#include "TitleGod.h"
#include "TitleSceneGUIManager.h"
#include "TitleScene//TitleSceneGUI.h"

struct TitleScene::Impl
{
	std::shared_ptr<TitleSceneGUI> _titlescene_gui;
	std::shared_ptr<TitleSceneGUIManager> _titlescene_gui_manager;

	RenderTexture _render_texture{ Scene::Size() };
};

TitleScene::TitleScene(const InitData& init_data) :
	IScene (init_data),
	p_impl(std::make_shared<Impl>())
{
	init();
}

void TitleScene::init()
{
	p_impl->_titlescene_gui = std::make_shared<TitleSceneGUI>();
	p_impl->_titlescene_gui_manager = std::make_shared<TitleSceneGUIManager>();

	p_impl->_titlescene_gui->init();
	p_impl->_titlescene_gui_manager->init();

	God::getInstance().setTitleSceneGUIManager(p_impl->_titlescene_gui_manager);
}

void TitleScene::update()
{
	double delta_time = Scene::DeltaTime();

	p_impl->_titlescene_gui->update(delta_time);
	p_impl->_titlescene_gui_manager->update(delta_time);
	Debug::getInstance().update(delta_time);

	auto scene_transition_data = God::getInstance().getSceneTransitionData();
	if(scene_transition_data.getDestinationSceneType() == Sc_Game)
	{
		God::getInstance().setSceneTransitionData(SceneTransitionData::None());
		changeScene(Sc_Game, scene_transition_data.getTransitionTimeMillisecond());
	}
}

void TitleScene::draw() const
{
	ClearPrint();
	{
		const ScopedRenderTarget2D target{ p_impl->_render_texture.clear(Palette::Black) };

		p_impl->_titlescene_gui->draw();
		Debug::getInstance().draw();
	}

	p_impl->_render_texture.draw();
}

void TitleScene::drawFadeIn(double t) const
{
	Vec2 pos = {0, 0};
	Vec2 size = { (1 - t) * Scene::Size().x, Scene::Size().y};
	RectF fade_in_background = {pos, size};

	draw();
	fade_in_background.draw(Palette::Black);
}

void TitleScene::drawFadeOut(double t) const
{
	Vec2 pos = {0, 0};
	Vec2 size = { t * Scene::Size().x, Scene::Size().y};
	RectF fade_in_background = {pos, size};

	draw();
	fade_in_background.draw(Palette::Black);
}
