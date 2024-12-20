﻿#include "stdafx.h"
#include "TitleSceneMenu.h"

#include "AssetKey.h"
#include "God.h"
#include "TitleGod.h"
#include "GUI/Component/Button.h"

struct TitleSceneMenu::Impl
{
	RectF _rectf;
	double _rectf_thickness = 12;

	bool _is_framed;

	Button _start_btn;
	Button _setting_btn;
	Button _exit_btn;

	void updateButton(double delta_time)
	{
		_start_btn.update(delta_time);
		_setting_btn.update(delta_time);
		_exit_btn.update(delta_time);

		//クリック判定
		if(_start_btn.getIsClicked())
		{
			auto titlescene_gui_manager = God::getInstance().getTitleSceneGUIManager();
			titlescene_gui_manager->onStartBtnClicked();
			_start_btn.setIsClicked(false);
		}
		if(_setting_btn.getIsClicked())
		{
			auto titlescene_gui_manager = God::getInstance().getTitleSceneGUIManager();
			titlescene_gui_manager->onSettingBtnClicked();
			_setting_btn.setIsClicked(false);
		}
		if(_exit_btn.getIsClicked())
		{
			auto titlescene_gui_manager = God::getInstance().getTitleSceneGUIManager();
			titlescene_gui_manager->onExitBtnClicked();
			_exit_btn.setIsClicked(false);
		}
	}

	void drawButton()
	{
		_start_btn.draw();
		_setting_btn.draw();
		_exit_btn.draw();
	}
};

TitleSceneMenu::TitleSceneMenu() : p_impl(std::make_shared<Impl>())
{
}

void TitleSceneMenu::init()
{
	init(Vec2{Scene::Width() / 2, Scene::Height() / 2}, true);
}

void TitleSceneMenu::init(Vec2 pos, bool is_framed)
{
	Vec2 btn_size = {180, 50};
	double btn_interval = 30 + btn_size.y;
	AssetNameView font_asset_name = AssetKey::pixel_b48;

	p_impl->_is_framed = is_framed;

	auto rectf_pos = pos;
	auto rectf_size = Vec2{400, 300};
	p_impl->_rectf = RectF{rectf_pos, rectf_size};

	auto base = p_impl->_rectf.pos + Vec2{p_impl->_rectf.w / 2, 60};
	auto resume_btn_pos = base;
	p_impl->_start_btn.init(RectF{Arg::center(resume_btn_pos), btn_size}, U"start", font_asset_name);

	auto setting_btn_pos = base + Vec2{0, btn_interval};
	p_impl->_setting_btn.init(RectF{Arg::center(setting_btn_pos), btn_size}, U"setting", font_asset_name);

	auto title_btn_pos = base + Vec2{0, btn_interval * 2};
	p_impl->_exit_btn.init(RectF{Arg::center(title_btn_pos), btn_size}, U"exit", font_asset_name);
}

void TitleSceneMenu::update(double delta_time)
{
	p_impl->updateButton(delta_time);
}

void TitleSceneMenu::draw() const
{
	if(p_impl->_is_framed)
	{
		p_impl->_rectf.draw(Palette::Black).drawFrame(p_impl->_rectf_thickness, Palette::White);
	}
	else
	{
		p_impl->_rectf.draw(Palette::Black);
	}
	p_impl->drawButton();
}
