#include "stdafx.h"
#include "GameClearScene.h"

#include "Debug.h"
#include "GameClearSceneGUI.h"
#include "GameClearSceneGUIManager.h"
#include "God.h"

struct GameClearScene::Impl
{
    std::shared_ptr<GameClearSceneGUI> _gameclear_scene_gui;
    std::shared_ptr<GameClearSceneGUIManager> _gameclear_scene_gui_manager;

    RenderTexture _render_texture{ Scene::Size() };
};

GameClearScene::GameClearScene(const InitData& init_data)
: IScene (init_data), p_impl(std::make_shared<Impl>())
{
    init();
}

void GameClearScene::init()
{
    p_impl->_gameclear_scene_gui = std::make_shared<GameClearSceneGUI>();
    p_impl->_gameclear_scene_gui_manager = std::make_shared<GameClearSceneGUIManager>();

    p_impl->_gameclear_scene_gui->init();
    p_impl->_gameclear_scene_gui_manager->init();

    God::getInstance().setGameClearSceneGUIManager(p_impl->_gameclear_scene_gui_manager);
}

void GameClearScene::update()
{
    double delta_time = Scene::DeltaTime();

    p_impl->_gameclear_scene_gui->update(delta_time);
    p_impl->_gameclear_scene_gui_manager->update(delta_time);
    Debug::getInstance().update(delta_time);

    auto scene_transition_data = God::getInstance().getSceneTransitionData();
    if(scene_transition_data.getDestinationSceneType() == Sc_Game)
    {
        God::getInstance().setSceneTransitionData(SceneTransitionData::None());
        changeScene(Sc_Game, 1000);
    }
    if(scene_transition_data.getDestinationSceneType() == Sc_Title)
    {
        God::getInstance().setSceneTransitionData(SceneTransitionData::None());
        changeScene(Sc_Title, 1000);
    }
}

void GameClearScene::draw() const
{
    ClearPrint();
    {
        const ScopedRenderTarget2D target{ p_impl->_render_texture.clear(Palette::Black) };

        p_impl->_gameclear_scene_gui->draw();
        Debug::getInstance().draw();
    }
    p_impl->_render_texture.draw();
}

void GameClearScene::drawFadeIn(double t) const
{
    Vec2 pos = {0, 0};
    Vec2 size = { (1 - t) * Scene::Size().x, Scene::Size().y};
    RectF fade_in_background = {pos, size};

    draw();
    fade_in_background.draw(Palette::Black);
}

void GameClearScene::drawFadeOut(double t) const
{
    Vec2 pos = {0, 0};
    Vec2 size = { t * Scene::Size().x, Scene::Size().y};
    RectF fade_in_background = {pos, size};

    draw();
    fade_in_background.draw(Palette::Black);
}
