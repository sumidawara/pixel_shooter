#include "stdafx.h"
#include "ShotManager.h"
#include "God.h"
#include "MathEx.h"
#include "Bullet/BulletContext.h"

struct ShotManager::Impl
{
	double _shot_accumulated_time;
	double _shot_interval; //PlayerStateから初期化

	std::vector<Vec2> getNWayDirections(Vec2 fire_dir, double spread_angle, int32 split_count) const
	{
		std::vector<Vec2> bullet_dir_list;
		auto normalized_fire_dir = fire_dir.normalized();

		if (split_count == 0)
		{
			return bullet_dir_list;
		}
		else if (split_count == 1)
		{
			bullet_dir_list.push_back(normalized_fire_dir);
			return bullet_dir_list;
		}
		else
		{
			double start_angle = -spread_angle / 2.0;
			double angle_step = spread_angle / (split_count - 1);

			for (int32 i = 0; i < split_count; ++i)
			{
				double angle = start_angle + i * angle_step;
				double angle_radian = angle * (Math::Pi / 180);
				Vec2 bullet_dir = normalized_fire_dir.rotated(angle_radian);
				bullet_dir_list.push_back(bullet_dir);
			}

			return bullet_dir_list;
		}
	}

	void shot()
	{
		auto camera_mat3x2 = God::getInstance().getCamera().getMat3x2().inverse();
		auto cursorWorldPos = camera_mat3x2.transformPoint(Cursor::PosF());

		auto player = God::getInstance().getPlayer();
		auto player_rectf = player.getRect();
		auto player_state = player.getPtrPlayerStateManager()->getPlayerState();

		BulletContext context;
		context.rectf = RectF{
			Arg::center_<Vec2>(player_rectf.center()), player_state.bullet_size, player_state.bullet_size
		};
		context.owner_type = T_Player;
		context.colorf = GraphicSetting::getSKY();
		context.speed = player_state.bullet_speed;
		context.range = player_state.bullet_range;
		context.damage = player_state.ranged_damage;
		context.reflection_count = player_state.reflection_count;
		context.penetration_count = player_state.penetration_count;

		auto front_dir = Vec2{cursorWorldPos - player_rectf.center()}.normalize();
		auto front_bullet_dir_list = getNWayDirections(front_dir,
		                                               player_state.front_angle,
		                                               player_state.n_way_front_shot);

		auto right_dir = front_dir.rotated90();
		auto right_bullet_dir_list = getNWayDirections(right_dir,
		                                               player_state.side_angle,
		                                               player_state.n_way_side_shot);

		auto back_dir = right_dir.rotated90();
		auto back_bullet_dir_list = getNWayDirections(back_dir,
		                                              player_state.back_angle,
		                                              player_state.n_way_back_shot);

		auto left_dir = back_dir.rotated90();
		auto left_bullet_dir_list = getNWayDirections(left_dir,
		                                              player_state.side_angle,
		                                              player_state.n_way_side_shot);

		//4つのリストを1つに合わせる
		std::vector<Vec2> bullet_dir_list;
		bullet_dir_list.reserve(
			front_bullet_dir_list.size() +
			right_bullet_dir_list.size() +
			back_bullet_dir_list.size() +
			left_bullet_dir_list.size());
		std::ranges::copy(front_bullet_dir_list, std::back_inserter(bullet_dir_list));
		std::ranges::copy(right_bullet_dir_list, std::back_inserter(bullet_dir_list));
		std::ranges::copy(back_bullet_dir_list, std::back_inserter(bullet_dir_list));
		std::ranges::copy(left_bullet_dir_list, std::back_inserter(bullet_dir_list));

		//bulletを生成
		for (auto& dir : bullet_dir_list)
		{
			context.direction = dir;

			auto ptr_bullet = std::make_shared<Bullet>();
			ptr_bullet->init(context);
			God::getInstance().getBulletManager()->addBullet(ptr_bullet);
		}
	}

	void mouse_pressed(double delta_time)
	{
		_shot_accumulated_time += delta_time;

		if (_shot_interval < _shot_accumulated_time)
		{
			shot();
			_shot_accumulated_time -= _shot_interval;
		}
	}

	void mouse_released(double delta_time)
	{
		if (_shot_interval > _shot_accumulated_time)
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

	if (MouseL.pressed())
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
