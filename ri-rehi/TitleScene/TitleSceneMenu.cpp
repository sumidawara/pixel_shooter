#include "stdafx.h"
#include "TitleSceneMenu.h"

#include "God.h"
#include "GUI/Component/Button.h"

struct TitleSceneMenu::Impl
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

			_resume_btn.setIsClicked(false);
		}
		if(_setting_btn.getIsClicked())
		{

			_setting_btn.setIsClicked(false);
		}
		if(_title_btn.getIsClicked())
		{

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

TitleSceneMenu::TitleSceneMenu() : p_impl(std::make_shared<Impl>())
{
}

void TitleSceneMenu::init()
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

void TitleSceneMenu::update(double delta_time)
{
	p_impl->updateButton(delta_time);
}

void TitleSceneMenu::draw() const
{
	p_impl->_rectf.draw(Palette::Black).drawFrame(p_impl->_rectf_thickness, Palette::White);
	p_impl->drawButton();
}
