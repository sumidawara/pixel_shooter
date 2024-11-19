#pragma once
#include "Enum.h"

using App = SceneManager<SceneType>;
class GameClearScene : public App::Scene
{
public:
    GameClearScene(const InitData& init_data);
    void init();
    void update() override;
    void draw() const override;
    void drawFadeIn(double t) const override;
    void drawFadeOut(double t) const override;

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;
};
