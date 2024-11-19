﻿#pragma once

class GameClearSceneGUI
{
public:
    GameClearSceneGUI();
    void init();
    void update(double delta_time);
    void draw() const;

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;
};
