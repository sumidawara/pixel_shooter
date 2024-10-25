﻿#pragma once
#include "AbilityManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Player/Player.h"
#include "World.h"
#include "GUI/GameSceneGUI.h"
#include "GUI/GameSceneGUIManager.h"

class God
{
public:
    God(const God&) = delete;
    God& operator=(const God&) = delete;
    God(God&&) = delete;
    God& operator=(God&&) = delete;

    static God& getInstance();

	World getWorld() const;
	Player getPlayer() const;
	Camera2D getCamera() const;

	void addICollidable(const std::shared_ptr<ICollidable>& ptr_icollidable) const;
	void removeICollidable(const std::shared_ptr<ICollidable>& ptr_icollidable);

	void addIParticle(const std::shared_ptr<IParticle>& ptr_iparticle) const;

	void addBullet(const std::shared_ptr<Bullet>& ptr_bullet) const;
	void removeBullet(const std::shared_ptr<Bullet>& ptr_bullet) const;

	std::shared_ptr<CollisionManager> getPtrCollisionManager();
	std::shared_ptr<GameSceneGUIManager> getPtrGameSceneGUIManager();
	std::shared_ptr<AbilityManager> getPtrAbilityManager();
	std::shared_ptr<TimeManager> getPtrTimeManager();

	SceneType getChangeSceneFlag() const;

	void setPtrWorld(const std::shared_ptr<World>& ptr_world) const;
	void setPtrPlayer(const std::shared_ptr<Player>& ptr_player) const;
	void setPtrCamera(const std::shared_ptr<Camera2D>& ptr_camera);
	void setCollisionManager(const std::shared_ptr<CollisionManager>& ptr_collision_manager);
	void setParticleManager(const std::shared_ptr<ParticleManager>& ptr_particle_manager);
	void setBulletManager(const std::shared_ptr<BulletManager>& ptr_bullet_manager);
	void setGameSceneGUI(const std::shared_ptr<GameSceneGUI>& ptr_gamescene_gui);
	void setGameSceneGUIManager(const std::shared_ptr<GameSceneGUIManager>& ptr_gamescene_gui_manager);
	void setAbilityManager(const std::shared_ptr<AbilityManager>& ptr_ability_manager);
	void setTimeManager(const std::shared_ptr<TimeManager>& ptr_time_manager);

	void setChangeSceneFlag(SceneType value);

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;

    God();
    ~God() = default;
};
