#include "stdafx.h"
#include "GameoverScene.h"

struct GameoverScene::Impl
{
	RenderTexture _render_texture{ Scene::Size() };
};

GameoverScene::GameoverScene(const InitData& init_data)
: IScene (init_data), p_impl(std::make_shared<Impl>())
{
}

void GameoverScene::init()
{
}

void GameoverScene::update()
{
}

void GameoverScene::draw() const
{
	{
		const ScopedRenderTarget2D target{ p_impl->_render_texture.clear(Palette::Black) };
	}
	p_impl->_render_texture.draw();
}

void GameoverScene::drawFadeIn(double t) const
{
	draw();
}

void GameoverScene::drawFadeOut(double t) const
{
	draw();
}
