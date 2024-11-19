#include "stdafx.h"

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
	_ptr_time_limit_manager = std::make_shared<TimeLimitManager>();
	_ptr_annotation = std::make_shared<Annotation>();

	_ptr_collision_manager->init();
	God::getInstance().setCollisionManager(_ptr_collision_manager);

	_ptr_enemy_manager->init();
	God::getInstance().setEnemyManager(_ptr_enemy_manager);

	auto stage_file_path = AssetKey::getStages()[God::getInstance().getStageNum()];
	_ptr_world->init({0, 0}, stage_file_path);
	God::getInstance().setPtrWorld(_ptr_world);

	_ptr_player->init(God::getInstance().getInitialPlayerPos());
	God::getInstance().setPtrPlayer(_ptr_player); //GamesceneGUIはPlayerに依存

	_ptr_exit->init(God::getInstance().getExitPos());
	_ptr_gamescene_gui->init();
	_ptr_gamescene_gui_manager->init();
	_ptr_particle_manager->init();
	_ptr_bullet_manager->init();
	_ptr_ability_manager->init();
	_ptr_time_manager->init();
	_ptr_time_limit_manager->init();
	_ptr_annotation->init();
	_cursor.init();

	_ptr_camera = std::make_shared<Camera2D>(God::getInstance().getInitialPlayerPos(), 1.0);
	_ptr_camera->setParameters(Camera2DParameters::NoControl());

	God::getInstance().setPtrCamera(_ptr_camera);
	God::getInstance().setPtrExit(_ptr_exit);
	God::getInstance().setParticleManager(_ptr_particle_manager);
	God::getInstance().setBulletManager(_ptr_bullet_manager);
	God::getInstance().setGameSceneGUI(_ptr_gamescene_gui);
	God::getInstance().setGameSceneGUIManager(_ptr_gamescene_gui_manager);
	God::getInstance().setAbilityManager(_ptr_ability_manager);
	God::getInstance().setTimeManager(_ptr_time_manager);
	God::getInstance().setTimeLimitManager(_ptr_time_limit_manager);

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
		_ptr_time_limit_manager->update(game_delta_time);
	}

	_ptr_camera->update();
	_ptr_camera->setTargetCenter(_ptr_player->getCenterPos());
	_cursor.update(system_delta_time);
	_ptr_ability_manager->update(system_delta_time);
	_ptr_gamescene_gui_manager->update(system_delta_time);
	_ptr_gamescene_gui->update(system_delta_time);
	_ptr_time_manager->update(system_delta_time);

	Debug::getInstance().update(system_delta_time);
	writeline();

	//ゲームオーバー判定 タイムオーバーも後々に実装
	if(_ptr_player->getPtrPlayerStateManager()->getPlayerState().current_hp == 0 ||
		_ptr_time_limit_manager->getTimeLimitInt() <= 0)
	{
		God::getInstance().setSceneTransitionData(SceneTransitionData::GameOver());
	}

	auto scene_transition_data = God::getInstance().getSceneTransitionData();
	//？？？ -> ゲームオーバー
	if(scene_transition_data.getDestinationSceneType() == Sc_Gameover)
	{
		God::getInstance().setSceneTransitionData(SceneTransitionData::None());
		changeScene(Sc_Gameover, scene_transition_data.getTransitionTimeMillisecond());
	}
	//？？？ -> タイトル
	if(scene_transition_data.getDestinationSceneType() == Sc_Title)
	{
		God::getInstance().setSceneTransitionData(SceneTransitionData::None());
		changeScene(Sc_Title, scene_transition_data.getTransitionTimeMillisecond());
	}
	//？？？ -> ゲームシーン
	if(scene_transition_data.getDestinationSceneType() == Sc_Game)
	{
		God::getInstance().setSceneTransitionData(SceneTransitionData::None());
		//ゲームシーン -> ゲームシーン
		if(scene_transition_data.getIsGameSceneToGameScene())
		{
			loadNextStage();
		}
		else
		{
			init();
		}
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
			_ptr_annotation->draw();
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

void GameScene::loadNextStage()
{
	_ptr_collision_manager->clearCollision();
	_ptr_enemy_manager->clearEnemy();

	_ptr_world->init({0, 0}, AssetKey::getStages()[God::getInstance().getStageNum()]);
	_ptr_player->setCenterPos(God::getInstance().getInitialPlayerPos());
	_ptr_exit->init(God::getInstance().getExitPos());
	_ptr_particle_manager->clearParticle();
	_ptr_bullet_manager->clearBullet();
	_ptr_time_limit_manager->reset();

	_ptr_camera = std::make_shared<Camera2D>(God::getInstance().getInitialPlayerPos(), 1.0);
	_ptr_camera->setParameters(Camera2DParameters::NoControl());
	God::getInstance().setPtrCamera(_ptr_camera);

	//ICollidableの登録 これは将来消す
	_ptr_collision_manager->addICollidable(_ptr_player);
	_ptr_collision_manager->addICollidable(_ptr_exit);
}

void GameScene::writeline() const
{
	if(Debug::getInstance().getDebugScreenIndex() == 1)
	{
		Debug::getInstance().writeline(1, U"StageNum : " + Format(God::getInstance().getStageNum()));
	}
}
