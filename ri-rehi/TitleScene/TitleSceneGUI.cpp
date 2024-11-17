#include "stdafx.h"
#include "TitleSceneGUI.h"

#include "AssetKey.h"
#include "TitleSceneMenu.h"

struct TitleSceneGUI::Impl
{
	TitleSceneMenu _titlescene_menu;
};

TitleSceneGUI::TitleSceneGUI() : p_impl(std::make_shared<Impl>())
{
}

void TitleSceneGUI::init()
{
	p_impl->_titlescene_menu.init(Vec2{200, 700}, false);
}

void TitleSceneGUI::update(double delta_time)
{
	p_impl->_titlescene_menu.update(delta_time);
}

void TitleSceneGUI::draw() const
{
	TextureAsset(AssetKey::bg_title).draw();
	FontAsset(AssetKey::pixel_b120)(U"Title").draw(200, 200);
	p_impl->_titlescene_menu.draw();
}
