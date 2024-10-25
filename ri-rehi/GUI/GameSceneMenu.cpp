#include "stdafx.h"
#include "GameSceneMenu.h"

#include "God.h"
#include "GraphicSetting.h"
#include "Component/Button.h"

struct GameSceneMenu::Impl
{
	RectF _rectf;
	double _rectf_thickness = 12;

	Button _resume_btn;
	Button _setting_btn;
	Button _title_btn;

	void updateButton(double delta_time)
	{
		_resume_btn.update(delta_time);
		_setting_btn.update(delta_time);
		_title_btn.update(delta_time);

		//クリック判定
		if(_resume_btn.getIsClicked())
		{
			auto gui_manager = God::getInstance().getPtrGameSceneGUIManager();
			gui_manager->onResumeBtnClicked();
			_resume_btn.setIsClicked(false);
		}
		if(_setting_btn.getIsClicked())
		{
			auto gui_manager = God::getInstance().getPtrGameSceneGUIManager();
			gui_manager->onSettingBtnClicked();
			_setting_btn.setIsClicked(false);
		}
		if(_title_btn.getIsClicked())
		{
			auto gui_manager = God::getInstance().getPtrGameSceneGUIManager();
			gui_manager->onTitleBtnClicked();
			_title_btn.setIsClicked(false);
		}
	}

	void drawButton()
	{
		_resume_btn.draw();
		_setting_btn.draw();
		_title_btn.draw();
	}
};

GameSceneMenu::GameSceneMenu() : p_impl(std::make_shared<Impl>())
{
}

void GameSceneMenu::init()
{
	Vec2 btn_size = {180, 50};
	double btn_interval = 30 + btn_size.y;
	AssetName font_asset_name = U"pixel_b48";

	auto center_pos = Arg::center(Scene::Width() / 2, Scene::Height() / 2);
	auto rectf_size = Vec2{400, 300};
	p_impl->_rectf = RectF{center_pos, rectf_size};

	auto base = p_impl->_rectf.pos + Vec2{p_impl->_rectf.w / 2, 60};
	auto resume_btn_pos = base;
	p_impl->_resume_btn.init(RectF{Arg::center(resume_btn_pos), btn_size}, U"resume", font_asset_name);

	auto setting_btn_pos = base + Vec2{0, btn_interval};
	p_impl->_setting_btn.init(RectF{Arg::center(setting_btn_pos), btn_size}, U"setting", font_asset_name);

	auto title_btn_pos = base + Vec2{0, btn_interval * 2};
	p_impl->_title_btn.init(RectF{Arg::center(title_btn_pos), btn_size}, U"title", font_asset_name);
}

void GameSceneMenu::update(double delta_time)
{
	p_impl->updateButton(delta_time);
}

void GameSceneMenu::draw() const
{
	p_impl->_rectf.draw(Palette::Black).drawFrame(p_impl->_rectf_thickness, Palette::White);
	p_impl->drawButton();
}
