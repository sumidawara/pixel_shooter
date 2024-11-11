#pragma once
#include "AbilityManager.h"
#include "Annotation.h"
#include "CollisionManager.h"
#include "Player/Player.h"
#include "World.h"
#include "Debug.h"
#include "Enemy/Slime.h"
#include "GUI/GameScene/GameSceneGUI.h"
#include "Particle/ParticleManager.h"
#include "Enemy/EnemyManager.h"
#include "Exit.h"
#include "TimeLimitManager.h"
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

	void loadNextStage();
	void writeline() const;

private:
	std::shared_ptr<World> _ptr_world;
	std::shared_ptr<Player> _ptr_player;
	std::shared_ptr<Exit> _ptr_exit;
	std::shared_ptr<EnemyManager> _ptr_enemy_manager;
	std::shared_ptr<ParticleManager> _ptr_particle_manager;
	std::shared_ptr<CollisionManager> _ptr_collision_manager;
	std::shared_ptr<BulletManager> _ptr_bullet_manager;
    std::shared_ptr<Camera2D> _ptr_camera;
    std::shared_ptr<GameSceneGUI> _ptr_gamescene_gui;
	std::shared_ptr<GameSceneGUIManager> _ptr_gamescene_gui_manager;
	std::shared_ptr<AbilityManager> _ptr_ability_manager;
	std::shared_ptr<TimeManager> _ptr_time_manager;
	std::shared_ptr<TimeLimitManager> _ptr_time_limit_manager;
	std::shared_ptr<Annotation> _ptr_annotation;

	RenderTexture _render_texture{ Scene::Size() };

	CursorEx _cursor;

};

