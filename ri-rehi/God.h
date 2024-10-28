#pragma once
#include "AbilityManager.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "SceneTransitionData.h"
#include "TimeManager.h"
#include "Player/Player.h"
#include "World.h"
#include "GameoverScene/GameoverSceneGUIManager.h"
#include "GUI/GameScene/GameSceneGUI.h"
#include "GUI/GameScene/GameSceneGUIManager.h"
#include "TitleScene/TitleSceneGUIManager.h"

class God
{
public:
    God(const God&) = delete;
    God& operator=(const God&) = delete;
    God(God&&) = delete;
    God& operator=(God&&) = delete;

    static God& getInstance();

	//ゲーム

	World getWorld() const;
	Player getPlayer() const;
	Camera2D getCamera() const;
	Vec2 getInitialPlayerPos() const;
	Vec2 getExitPos() const;

	std::shared_ptr<CollisionManager> getPtrCollisionManager();
	std::shared_ptr<ParticleManager> getPtrParticleManager();
	std::shared_ptr<BulletManager> getBulletManager();
	std::shared_ptr<GameSceneGUIManager> getPtrGameSceneGUIManager();
	std::shared_ptr<AbilityManager> getPtrAbilityManager();
	std::shared_ptr<TimeManager> getPtrTimeManager();
	std::shared_ptr<EnemyManager> getEnemyManager();

	void setPtrWorld(const std::shared_ptr<World>& ptr_world) const;
	void setPtrPlayer(const std::shared_ptr<Player>& ptr_player) const;
	void setPtrCamera(const std::shared_ptr<Camera2D>& ptr_camera);
	void setInitialPlayerPos(Vec2 pos);
	void setExitPos(Vec2 pos);

	void setCollisionManager(const std::shared_ptr<CollisionManager>& ptr_collision_manager);
	void setParticleManager(const std::shared_ptr<ParticleManager>& ptr_particle_manager);
	void setBulletManager(const std::shared_ptr<BulletManager>& ptr_bullet_manager);
	void setGameSceneGUI(const std::shared_ptr<GameSceneGUI>& ptr_gamescene_gui);
	void setGameSceneGUIManager(const std::shared_ptr<GameSceneGUIManager>& ptr_gamescene_gui_manager);
	void setAbilityManager(const std::shared_ptr<AbilityManager>& ptr_ability_manager);
	void setTimeManager(const std::shared_ptr<TimeManager>& ptr_time_manager);
	void setEnemyManager(const std::shared_ptr<EnemyManager>& ptr_enemy_manager);

	//タイトル
	std::shared_ptr<TitleSceneGUIManager> getTitleSceneGUIManager() const;

	void setTitleSceneGUIManager(const std::shared_ptr<TitleSceneGUIManager>& value);

	//ゲームオーバー
	std::shared_ptr<GameoverSceneGUIManager> getGameoverSceneGUIManager() const;

	void setGameoverSceneGUIManager(const std::shared_ptr<GameoverSceneGUIManager>& value);

	//共通
	SceneTransitionData getSceneTransitionData() const;
	void setSceneTransitionData(const SceneTransitionData& value);

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;

    God();
    ~God() = default;
};
