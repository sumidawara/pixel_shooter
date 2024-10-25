#include "stdafx.h"
#include "TitleScene.h"

struct TitleScene::Impl
{

};

TitleScene::TitleScene(const InitData& init_data) : IScene (init_data), p_impl(std::make_shared<Impl>())
{
}

void TitleScene::init()
{
}

void TitleScene::update()
{
	IScene<SceneType, void>::update();
}

void TitleScene::draw() const
{
	IScene<SceneType, void>::draw();
}

void TitleScene::drawFadeIn(double t) const
{
	IScene<SceneType, void>::drawFadeIn(t);
}

void TitleScene::drawFadeOut(double t) const
{
	IScene<SceneType, void>::drawFadeOut(t);
}
