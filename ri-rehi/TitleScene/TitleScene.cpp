#include "stdafx.h"
#include "TitleScene.h"

#include "TitleScene//TitleSceneGUI.h"

struct TitleScene::Impl
{
	TitleSceneGUI _titlescene_gui;

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
	p_impl->_titlescene_gui.init();
}

void TitleScene::update()
{
}

void TitleScene::draw() const
{
	{
		const ScopedRenderTarget2D target{ p_impl->_render_texture.clear(Palette::Black) };

		p_impl->_titlescene_gui.draw();
	}

	p_impl->_render_texture.draw();
}

void TitleScene::drawFadeIn(double t) const
{
	draw();
}

void TitleScene::drawFadeOut(double t) const
{
	draw();
}
