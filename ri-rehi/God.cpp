#include "stdafx.h"
#include "God.h"

class GameClearSceneGUIManager;

struct God::Impl
{
public:
	//デバッグ用
	int32 INITIAL_STAGE_NUM = 9;

	//ゲーム
	int32 _stage_num = INITIAL_STAGE_NUM;
	std::shared_ptr<World> _ptr_world;
	std::shared_ptr<Player> _ptr_player;
	std::shared_ptr<Camera2D> _ptr_camera;
	Vec2 _initial_player_pos;
	Vec2 _exit_pos;

	std::shared_ptr<CollisionManager> _ptr_collision_manager;
	std::shared_ptr<ParticleManager> _ptr_particle_manager;
	std::shared_ptr<BulletManager> _ptr_bullet_manager;
	std::shared_ptr<GameSceneGUI> _ptr_gamescene_gui;
	std::shared_ptr<GameSceneGUIManager> _ptr_gamescene_gui_manager;
	std::shared_ptr<AbilityManager> _ptr_ability_manager;
	std::shared_ptr<TimeManager> _ptr_time_manager;
	std::shared_ptr<TimeLimitManager> _ptr_time_limit_manager;
	std::shared_ptr<EnemyManager> _ptr_enemy_manager;
	std::shared_ptr<Exit> _ptr_exit;

	//タイトル
	std::shared_ptr<TitleSceneGUIManager> _ptr_titlescene_gui_manager;

	//ゲームオーバー
	std::shared_ptr<GameoverSceneGUIManager> _ptr_gameoverscene_gui_manager;

    //ゲームクリア
    std::shared_ptr<GameClearSceneGUIManager> _ptr_gameclearscene_gui_manager;
    
	//共通
	SceneTransitionData _scene_transition_data;
};

God::God() : p_impl(std::make_shared<Impl>())
{
}

God& God::getInstance()
{
	static God instance;
	return instance;
}

int32 God::GET_INITIAL_STAGE_NUM()
{
	return p_impl->INITIAL_STAGE_NUM;
}

int32 God::getStageNum() const
{
	return p_impl->_stage_num;
}

Player God::getPlayer() const
{
	return *p_impl->_ptr_player;
}

Camera2D God::getCamera() const
{
	return *p_impl->_ptr_camera;
}

Vec2 God::getInitialPlayerPos() const
{
	return p_impl->_initial_player_pos;
}

Vec2 God::getExitPos() const
{
	return p_impl->_exit_pos;
}

World God::getWorld() const
{
	return *p_impl->_ptr_world;
}

std::shared_ptr<CollisionManager> God::getPtrCollisionManager() const
{
	return p_impl->_ptr_collision_manager;
}

std::shared_ptr<ParticleManager> God::getPtrParticleManager() const
{
	return p_impl->_ptr_particle_manager;
}

std::shared_ptr<BulletManager> God::getBulletManager() const
{
	return p_impl->_ptr_bullet_manager;
}

std::shared_ptr<GameSceneGUIManager> God::getPtrGameSceneGUIManager() const
{
	return p_impl->_ptr_gamescene_gui_manager;
}

std::shared_ptr<AbilityManager> God::getPtrAbilityManager() const
{
	return p_impl->_ptr_ability_manager;
}

std::shared_ptr<TimeManager> God::getPtrTimeManager() const
{
	return p_impl->_ptr_time_manager;
}

std::shared_ptr<TimeLimitManager> God::getTimeLimitManager() const
{
	return p_impl->_ptr_time_limit_manager;
}

std::shared_ptr<EnemyManager> God::getEnemyManager() const
{
	return p_impl->_ptr_enemy_manager;
}

std::shared_ptr<Exit> God::getPtrExit() const
{
	return p_impl->_ptr_exit;
}

//セッター

void God::setStageNum(int32 value)
{
	p_impl->_stage_num = value;
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

void God::setInitialPlayerPos(Vec2 pos)
{
	p_impl->_initial_player_pos = pos;
}

void God::setExitPos(Vec2 pos)
{
	p_impl->_exit_pos = pos;
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

void God::setTimeLimitManager(const std::shared_ptr<TimeLimitManager>& ptr_time_limit_manager)
{
	p_impl->_ptr_time_limit_manager = ptr_time_limit_manager;
}

void God::setEnemyManager(const std::shared_ptr<EnemyManager>& ptr_enemy_manager)
{
	p_impl->_ptr_enemy_manager = ptr_enemy_manager;
}

void God::setPtrExit(const std::shared_ptr<Exit>& ptr_exit)
{
	p_impl->_ptr_exit = ptr_exit;
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

std::shared_ptr<GameClearSceneGUIManager> God::getGameClearSceneGUIManager() const
{
    return p_impl->_ptr_gameclearscene_gui_manager;
}

void God::setGameClearSceneGUIManager(const std::shared_ptr<GameClearSceneGUIManager>& value)
{
    p_impl->_ptr_gameclearscene_gui_manager = value;
}


//共通

SceneTransitionData God::getSceneTransitionData() const
{
	return p_impl->_scene_transition_data;
}

void God::setSceneTransitionData(const SceneTransitionData& value)
{
	p_impl->_scene_transition_data = value;
}
