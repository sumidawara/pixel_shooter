#pragma once
#include "AbilityManager.h"
#include "CollisionManager.h"
#include "Player/Player.h"
#include "World.h"
#include "Debug.h"
#include "Slime.h"
#include "GUI/GameScene/GameSceneGUI.h"
#include "Particle/ParticleManager.h"
#include "EnemyManager.h"
#include "TimeManager.h"
#include "GUI/CursorEx.h"
#include "GUI/GameScene/GameSceneGUIManager.h"

using App = SceneManager<SceneType>;

class GameScene : public App::Scene
{
public:
	GameScene(const InitData& init);
	void init();

	void update() override;
	void draw() const override;
	void drawFadeIn(double t) const override;
	void drawFadeOut(double t) const override;

private:
	std::shared_ptr<World> _ptr_world;
	std::shared_ptr<Player> _ptr_player;
	std::shared_ptr<EnemyManager> _ptr_enemy_manager;
	std::shared_ptr<ParticleManager> _ptr_particle_manager;
	std::shared_ptr<CollisionManager> _ptr_collision_manager;
	std::shared_ptr<BulletManager> _ptr_bullet_manager;
    std::shared_ptr<Camera2D> _ptr_camera;
    std::shared_ptr<GameSceneGUI> _ptr_gamescene_gui;
	std::shared_ptr<GameSceneGUIManager> _ptr_gamescene_gui_manager;
	std::shared_ptr<AbilityManager> _ptr_ability_manager;
	std::shared_ptr<TimeManager> _ptr_time_manager;

	RenderTexture _render_texture{ Scene::Size() };

	CursorEx _cursor;

};

