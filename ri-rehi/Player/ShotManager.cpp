#include "stdafx.h"
#include "ShotManager.h"
#include "God.h"
#include "Bullet/BulletContext.h"

struct ShotManager::Impl
{
	double _shot_accumulated_time;
	double _shot_interval; //PlayerStateから初期化

	void shot()
	{
		auto camera_mat3x2 = God::getInstance().getCamera().getMat3x2().inverse();
		auto cursorWorldPos = camera_mat3x2.transformPoint(Cursor::PosF());

		auto player = God::getInstance().getPlayer();
		auto player_rectf = player.getRect();
		auto player_state = player.getPtrPlayerStateManager()->getPlayerState();

		BulletContext context;
		context.rectf = RectF{Arg::center_<Vec2>(player_rectf.center()), player_state.bullet_size, player_state.bullet_size};
		context.direction = Vec2{cursorWorldPos - player_rectf.center()}.normalize();
		context.owner_type = T_Player;
		context.speed = player_state.bullet_speed;
		context.range = player_state.bullet_range;
		context.damage = player_state.ranged_damage;
		context.reflection_count = player_state.reflection_count;
		context.penetration_count = player_state.penetration_count;



		auto ptr_bullet = std::make_shared<Bullet>();
		ptr_bullet->init(context);
		God::getInstance().getBulletManager()->addBullet(ptr_bullet);
	}

	void mouse_pressed(double delta_time)
	{
		_shot_accumulated_time += delta_time;

		if(_shot_interval < _shot_accumulated_time)
		{
			shot();
			_shot_accumulated_time -= _shot_interval;
		}
	}

	void mouse_released(double delta_time)
	{
		if(_shot_interval > _shot_accumulated_time)
		{
			_shot_accumulated_time += delta_time;
		}
	}
};

ShotManager::ShotManager() : p_impl(std::make_shared<Impl>())
{
}

void ShotManager::init()
{
}

void ShotManager::update(double delta_time)
{
	auto player_state = God::getInstance().getPlayer().getPlayerState();
	p_impl->_shot_interval = player_state.shot_interval;

	if(MouseL.pressed())
	{
		p_impl->mouse_pressed(delta_time);
	}
	else
	{
		p_impl->mouse_released(delta_time);
	}
}

void ShotManager::draw() const
{
}
