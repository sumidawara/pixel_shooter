﻿#include "stdafx.h"
#include "God.h"

struct God::Impl
{
public:
	std::shared_ptr<World> _ptr_world;
	std::shared_ptr<Player> _ptr_player;
	std::shared_ptr<Camera2D> _ptr_camera;
	std::shared_ptr<CollisionManager> _ptr_collision_manager;
	std::shared_ptr<ParticleManager> _ptr_particle_manager;
	std::shared_ptr<BulletManager> _ptr_bullet_manager;
	std::shared_ptr<GameSceneGUI> _ptr_gamescene_gui;
	std::shared_ptr<GameSceneGUIManager> _ptr_gamescene_gui_manager;
	std::shared_ptr<AbilityManager> _ptr_ability_manager;
	std::shared_ptr<TimeManager> _ptr_time_manager;

	SceneType _change_scene_flag;
};

God::God() : p_impl(std::make_shared<Impl>())
{
}

God& God::getInstance()
{
	static God instance;
	return instance;
}

Player God::getPlayer() const
{
	return *p_impl->_ptr_player;
}

Camera2D God::getCamera() const
{
	return *p_impl->_ptr_camera;
}

World God::getWorld() const
{
	return *p_impl->_ptr_world;
}

void God::addICollidable(const std::shared_ptr<ICollidable>& ptr_icollidable) const
{
	p_impl->_ptr_collision_manager->addICollidable(ptr_icollidable);
}

void God::removeICollidable(const std::shared_ptr<ICollidable>& ptr_icollidable)
{
	p_impl->_ptr_collision_manager->removeICollidable(ptr_icollidable);
}

std::shared_ptr<CollisionManager> God::getPtrCollisionManager()
{
	return p_impl->_ptr_collision_manager;
}

void God::addIParticle(const std::shared_ptr<IParticle>& ptr_iparticle) const
{
	p_impl->_ptr_particle_manager->addParticle(ptr_iparticle);
}

void God::addBullet(const std::shared_ptr<Bullet>& ptr_bullet) const
{
	p_impl->_ptr_bullet_manager->addBullet(ptr_bullet);
}

void God::removeBullet(const std::shared_ptr<Bullet>& ptr_bullet) const
{
	p_impl->_ptr_bullet_manager->removeBullet(ptr_bullet);
}

std::shared_ptr<GameSceneGUIManager> God::getPtrGameSceneGUIManager()
{
	return p_impl->_ptr_gamescene_gui_manager;
}

std::shared_ptr<AbilityManager> God::getPtrAbilityManager()
{
	return p_impl->_ptr_ability_manager;
}

std::shared_ptr<TimeManager> God::getPtrTimeManager()
{
	return p_impl->_ptr_time_manager;
}

SceneType God::getChangeSceneFlag() const
{
	return p_impl->_change_scene_flag;
}

void God::setPtrWorld(const std::shared_ptr<World>& ptr_world) const
{
	p_impl->_ptr_world = ptr_world;
}

void God::setPtrPlayer(const std::shared_ptr<Player>& ptr_player) const
{
	p_impl->_ptr_player = ptr_player;
}

void God::setPtrCamera(const std::shared_ptr<Camera2D>& ptr_camera)
{
	p_impl->_ptr_camera = ptr_camera;
}

void God::setCollisionManager(const std::shared_ptr<CollisionManager>& ptr_collision_manager)
{
	p_impl->_ptr_collision_manager = ptr_collision_manager;
}

void God::setParticleManager(const std::shared_ptr<ParticleManager>& ptr_particle_manager)
{
	p_impl->_ptr_particle_manager = ptr_particle_manager;
}

void God::setBulletManager(const std::shared_ptr<BulletManager>& ptr_bullet_manager)
{
	p_impl->_ptr_bullet_manager = ptr_bullet_manager;
}

void God::setGameSceneGUI(const std::shared_ptr<GameSceneGUI>& ptr_gamescene_gui)
{
	p_impl->_ptr_gamescene_gui = ptr_gamescene_gui;
}

void God::setGameSceneGUIManager(const std::shared_ptr<GameSceneGUIManager>& ptr_gamescene_gui_manager)
{
	p_impl->_ptr_gamescene_gui_manager = ptr_gamescene_gui_manager;
}

void God::setAbilityManager(const std::shared_ptr<AbilityManager>& ptr_ability_manager)
{
	p_impl->_ptr_ability_manager = ptr_ability_manager;
}

void God::setTimeManager(const std::shared_ptr<TimeManager>& ptr_time_manager)
{
	p_impl->_ptr_time_manager = ptr_time_manager;
}

void God::setChangeSceneFlag(SceneType value)
{
	p_impl->_change_scene_flag = value;
}