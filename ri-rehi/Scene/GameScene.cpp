#include "stdafx.h"

#include "memory"

#include "GameScene.h"
#include "Bullet/Bullet.h"
#include "DebugSetting.h"
#include "AssetManager.h"
#include "God.h"

GameScene::GameScene(const InitData& init)
	: IScene{ init }
{
	_ptr_world = std::make_shared<World>();
	_ptr_player = std::make_shared<Player>();
	_ptr_particle_manager = std::make_shared<ParticleManager>();
	_ptr_bullet_manager = std::make_shared<BulletManager>();
	_ptr_enemy_manager = std::make_shared<EnemyManager>();
	_ptr_camera = std::make_shared<Camera2D>(_ptr_player->getCenterPos(), 1.0);
	_ptr_gamescene_gui = std::make_shared<GameSceneGUI>();
	_ptr_gamescene_gui_manager = std::make_shared<GameSceneGUIManager>();
	_ptr_collision_manager = std::make_shared<CollisionManager>();
	_ptr_ability_manager = std::make_shared<AbilityManager>();
	_ptr_time_manager = std::make_shared<TimeManager>();

	_ptr_collision_manager->init();
	God::getInstance().setCollisionManager(_ptr_collision_manager);

	_ptr_world->init({0, 0}, U"resources/world/world.json");
    _ptr_player->init({200, 200});
	_ptr_camera->setParameters(Camera2DParameters::NoControl());
	_ptr_gamescene_gui->init();
	_ptr_gamescene_gui_manager->init();
	_ptr_particle_manager->init();
	_ptr_ability_manager->init();
	_ptr_time_manager->init();
	_cursor.init();

	God::getInstance().setPtrWorld(_ptr_world);
    God::getInstance().setPtrPlayer(_ptr_player);
	God::getInstance().setPtrCamera(_ptr_camera);
	God::getInstance().setParticleManager(_ptr_particle_manager);
	God::getInstance().setBulletManager(_ptr_bullet_manager);
	God::getInstance().setGameSceneGUI(_ptr_gamescene_gui);
	God::getInstance().setGameSceneGUIManager(_ptr_gamescene_gui_manager);
	God::getInstance().setAbilityManager(_ptr_ability_manager);
	God::getInstance().setTimeManager(_ptr_time_manager);
	AssetManager::registerAsset();

	_ptr_enemy_manager->init();

    Debug::getInstance().init();

	//ICollidableの登録
	God::getInstance().addICollidable(_ptr_player);
	Layer terrain_object_layer = God::getInstance().getWorld().getLayer(L_TerrainObject);
	for(auto ptr_block : terrain_object_layer.getBlockPtrList())
	{
		if(ptr_block->getId() != -1)
		{
			God::getInstance().addICollidable(ptr_block);
		}
	}
}

void GameScene::init()
{
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

	if(_ptr_player->getPtrPlayerStateManager()->getPlayerState().current_hp == 0)
	{
		changeScene(Sc_Gameover);
	}
	if(God::getInstance().getChangeSceneFlag() == Sc_Title)
	{
		changeScene(Sc_Title);
	}

	//Debug::getInstance().writeline(9, FileSystem::CurrentDirectory());
}

void GameScene::draw() const
{
	ClearPrint();

	{
		const ScopedRenderTarget2D target{ _render_texture.clear(Palette::Black) };
		{
			const Transformer2D transform = _ptr_camera->createTransformer();

			_ptr_world->draw();
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
		//const ScopedCustomShader2D shader{PixelShaderAsset{U"ps_default"}};

		(void)_render_texture.draw(0, 0);
	}
}


void GameScene::drawFadeIn(double t) const
{
	draw();
}

void GameScene::drawFadeOut(double t) const
{
	draw();
}
