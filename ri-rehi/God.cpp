#include "stdafx.h"
#include "God.h"

struct God::Impl
{
public:
	//ゲーム
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

	//タイトル
	std::shared_ptr<TitleSceneGUIManager> _ptr_titlescene_gui_manager;

	//ゲームオーバー
	std::shared_ptr<GameoverSceneGUIManager> _ptr_gameoverscene_gui_manager;

	//共通
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

std::shared_ptr<CollisionManager> God::getPtrCollisionManager()
{
	return p_impl->_ptr_collision_manager;
}

std::shared_ptr<ParticleManager> God::getPtrParticleManager()
{
	return p_impl->_ptr_particle_manager;
}

std::shared_ptr<BulletManager> God::getBulletManager()
{
	return p_impl->_ptr_bullet_manager;
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

std::shared_ptr<TitleSceneGUIManager> God::getTitleSceneGUIManager() const
{
	return p_impl->_ptr_titlescene_gui_manager;
}

void God::setTitleSceneGUIManager(const std::shared_ptr<TitleSceneGUIManager>& value)
{
	p_impl->_ptr_titlescene_gui_manager = value;
}

std::shared_ptr<GameoverSceneGUIManager> God::getGameoverSceneGUIManager() const
{
	return p_impl->_ptr_gameoverscene_gui_manager;
}

void God::setGameoverSceneGUIManager(const std::shared_ptr<GameoverSceneGUIManager>& value)
{
	p_impl->_ptr_gameoverscene_gui_manager = value;
}


//共通

SceneType God::getChangeSceneFlag() const
{
	return p_impl->_change_scene_flag;
}
void God::setChangeSceneFlag(SceneType value)
{
	p_impl->_change_scene_flag = value;
}
