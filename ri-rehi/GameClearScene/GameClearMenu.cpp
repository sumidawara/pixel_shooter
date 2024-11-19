#include "stdafx.h"
#include "GameClearMenu.h"

#include "AssetKey.h"
#include "God.h"
#include "GUI/Component/Button.h"

struct GameClearMenu::Impl
{
    RectF _rectf;
    double _rectf_thickness = 12;

    Button _restart_btn;
    Button _title_btn;

    void updateButton(double delta_time)
    {
        _restart_btn.update(delta_time);
        _title_btn.update(delta_time);

        //クリック判定
        if(_restart_btn.getIsClicked())
        {
            auto gameover_scene_gui_manager = God::getInstance().getGameoverSceneGUIManager();
            gameover_scene_gui_manager->onRestartBtnClicked();
            _restart_btn.setIsClicked(false);
        }
        if(_title_btn.getIsClicked())
        {
            auto gameover_scene_gui_manager = God::getInstance().getGameoverSceneGUIManager();
            gameover_scene_gui_manager->onTitleBtnClicked();
            _title_btn.setIsClicked(false);
        }
    }

    void drawButton()
    {
        _restart_btn.draw();
        _title_btn.draw();
    }
};

GameClearMenu::GameClearMenu() : p_impl(std::make_shared<Impl>())
{
}

void GameClearMenu::init()
{
    Vec2 btn_size = {180, 50};
    double btn_interval = 30 + btn_size.y;
    AssetNameView font_asset_name = AssetKey::pixel_b48;

    auto center_pos = Arg::center(Scene::Width() / 2, Scene::Height() / 2);
    auto rectf_size = Vec2{400, 300};
    p_impl->_rectf = RectF{center_pos, rectf_size};

    auto base = p_impl->_rectf.pos + Vec2{p_impl->_rectf.w / 2, 60};
    auto resume_btn_pos = base;
    p_impl->_restart_btn.init(RectF{Arg::center(resume_btn_pos), btn_size}, U"restart", font_asset_name);

    auto setting_btn_pos = base + Vec2{0, btn_interval};
    p_impl->_title_btn.init(RectF{Arg::center(setting_btn_pos), btn_size}, U"title", font_asset_name);
}

void GameClearMenu::update(double delta_time)
{
    p_impl->updateButton(delta_time);
}

void GameClearMenu::draw() const
{
    p_impl->_rectf.draw(Palette::Black).drawFrame(p_impl->_rectf_thickness, Palette::White);
    p_impl->drawButton();
}
