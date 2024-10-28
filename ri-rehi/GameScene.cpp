﻿#include "stdafx.h"

#include "memory"

#include "GameScene.h"

#include "AssetKey.h"
#include "Bullet/Bullet.h"
#include "DebugSetting.h"
#include "AssetManager.h"
#include "God.h"

GameScene::GameScene(const InitData& init_data)
	: IScene{ init_data }
{
	init();
}

void GameScene::init()
{
	_ptr_world = std::make_shared<World>();
	_ptr_player = std::make_shared<Player>();
	_ptr_exit = std::make_shared<Exit>();
	_ptr_particle_manager = std::make_shared<ParticleManager>();
	_ptr_bullet_manager = std::make_shared<BulletManager>();
	_ptr_enemy_manager = std::make_shared<EnemyManager>();
	_ptr_gamescene_gui = std::make_shared<GameSceneGUI>();
	_ptr_gamescene_gui_manager = std::make_shared<GameSceneGUIManager>();
	_ptr_collision_manager = std::make_shared<CollisionManager>();
	_ptr_ability_manager = std::make_shared<AbilityManager>();
	_ptr_time_manager = std::make_shared<TimeManager>();

	_ptr_collision_manager->init();
	God::getInstance().setCollisionManager(_ptr_collision_manager);

	_ptr_enemy_manager->init();
	God::getInstance().setEnemyManager(_ptr_enemy_manager);

	_ptr_world->init({0, 0}, AssetKey::getStages()[0]);
	God::getInstance().setPtrWorld(_ptr_world);

	_ptr_player->init(God::getInstance().getInitialPlayerPos());
	_ptr_exit->init(God::getInstance().getExitPos());
	_ptr_gamescene_gui->init();
	_ptr_gamescene_gui_manager->init();
	_ptr_particle_manager->init();
	_ptr_ability_manager->init();
	_ptr_time_manager->init();
	_cursor.init();

	_ptr_camera = std::make_shared<Camera2D>(God::getInstance().getInitialPlayerPos(), 1.0);
	_ptr_camera->setParameters(Camera2DParameters::NoControl());

	God::getInstance().setPtrPlayer(_ptr_player);
	God::getInstance().setPtrCamera(_ptr_camera);
	God::getInstance().setParticleManager(_ptr_particle_manager);
	God::getInstance().setBulletManager(_ptr_bullet_manager);
	God::getInstance().setGameSceneGUI(_ptr_gamescene_gui);
	God::getInstance().setGameSceneGUIManager(_ptr_gamescene_gui_manager);
	God::getInstance().setAbilityManager(_ptr_ability_manager);
	God::getInstance().setTimeManager(_ptr_time_manager);
	AssetManager::registerAsset();

	Debug::getInstance().init();

	//ICollidableの登録 これは将来消す
	_ptr_collision_manager->addICollidable(_ptr_player);
	_ptr_collision_manager->addICollidable(_ptr_exit);
}

void GameScene::update()
{
	double game_delta_time = Scene::DeltaTime() * _ptr_time_manager->getGameTimeScale();
	double system_delta_time = Scene::DeltaTime() * _ptr_time_manager->getSystemTimeScale();

	auto is_manually_paused = _ptr_time_manager->getIsManuallyPaused();
	auto is_forcibly_paused = _ptr_time_manager->getIsForciblyPaused();
	if((not is_manually_paused) and (not is_forcibly_paused))
	{
		_ptr_world->update(game_delta_time);
		_ptr_exit->update(game_delta_time);
		_ptr_player->update(game_delta_time);
		_ptr_enemy_manager->update(game_delta_time);
		_ptr_particle_manager->update(game_delta_time);
		_ptr_collision_manager->update(game_delta_time);
		_ptr_bullet_manager->update(game_delta_time);
	}

	_ptr_camera->update();
	_ptr_camera->setTargetCenter(_ptr_player->getCenterPos());
	_cursor.update(system_delta_time);
	_ptr_gamescene_gui->update(system_delta_time);
	_ptr_gamescene_gui_manager->update(system_delta_time);
	_ptr_ability_manager->update(system_delta_time);
	_ptr_time_manager->update(system_delta_time);
	Debug::getInstance().update(system_delta_time);

	auto scene_transition_data = God::getInstance().getSceneTransitionData();
	if(_ptr_player->getPtrPlayerStateManager()->getPlayerState().current_hp == 0)
	{
		God::getInstance().setSceneTransitionData(SceneTransitionData::None());
		changeScene(Sc_Gameover, scene_transition_data.getTransitionTimeMillisecond());
	}
	if(scene_transition_data.getDestinationSceneType() == Sc_Title)
	{
		God::getInstance().setSceneTransitionData(SceneTransitionData::None());
		changeScene(Sc_Title, scene_transition_data.getTransitionTimeMillisecond());
	}
	if(scene_transition_data.getDestinationSceneType() == Sc_Game)
	{
		God::getInstance().setSceneTransitionData(SceneTransitionData::None());
		if(scene_transition_data.getIsGameSceneToGameScene())
		{

		}
		init();
	}
}

void GameScene::draw() const
{
	ClearPrint();

	{
		const ScopedRenderTarget2D target{ _render_texture.clear(Palette::Black) };
		{
			const Transformer2D transform = _ptr_camera->createTransformer();

			_ptr_world->draw();
			_ptr_exit->draw();
			_ptr_enemy_manager->draw();
			_ptr_player->draw();
			_ptr_bullet_manager->draw();
			_ptr_particle_manager->draw();
		}

		_ptr_gamescene_gui->draw();
		_cursor.draw();

		Debug::getInstance().draw();
	}

	{
		//const ScopedCustomShader2D shader{PixelShaderAsset{AssetKey::ps_default}};

		(void)_render_texture.draw(0, 0);
	}
}


void GameScene::drawFadeIn(double t) const
{
	Vec2 pos = {0, 0};
	Vec2 size = { (1 - t) * Scene::Size().x, Scene::Size().y};
	RectF fade_in_background = {pos, size};

	draw();
	fade_in_background.draw(Palette::Black);
}

void GameScene::drawFadeOut(double t) const
{
	Vec2 pos = {0, 0};
	Vec2 size = { t * Scene::Size().x, Scene::Size().y};
	RectF fade_in_background = {pos, size};

	draw();
	fade_in_background.draw(Palette::Black);
}
