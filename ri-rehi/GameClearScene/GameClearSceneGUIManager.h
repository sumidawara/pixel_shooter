#pragma once

class GameClearSceneGUIManager
{
public:
    GameClearSceneGUIManager();
    void init();
    void update(double delta_time);
    void draw() const;

    void onRestartBtnClicked();
    void onTitleBtnClicked();

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;
};
