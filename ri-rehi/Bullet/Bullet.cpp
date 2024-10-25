#include "stdafx.h"
#include "Bullet.h"

#include "BulletContext.h"
#include "Particle/BulletParticle.h"
#include "CollisionUtil.h"
#include "Debug.h"
#include "God.h"
#include "MathEx.h"

struct Bullet::Impl
{
	//initで初期化される変数
	RectF _rectf;
	Vec2 _direction;
	ICollidableType _owner_type;
	double _speed;
	double _range;
	int32 _damage;
	int32 _reflection_count;
	int32 _penetration_count;

	double _previous_move_delta = 0.0;
	double _move_amount = 0.0;
	bool _is_active = true;

	void move(double delta_time)
	{
		Vec2 delta = _direction * (_speed * delta_time);

		_rectf.moveBy(delta.x, delta.y);
		_previous_move_delta = delta.length();
		_move_amount += delta.length();
		if (_move_amount > _range)
		{
			destroy();
		}
	}

	void reflect(const ICollidable& other, int32& reflection_count)
	{
		//ぶつかったときにひとつ前の状態に戻してから、そこからrayを飛ばして頂点をリストで取得し
		//弾の座標と最も近い交点をふくむものがぶつかった面
		//弾がでかすぎると不可能

		reflection_count -= 1;

		Vec2 reverse_delta = -_direction * _previous_move_delta;
		RectF previous_rectf = _rectf.movedBy(reverse_delta);

		double RAY_LENGTH = 1000;
		Line ray = {previous_rectf.center(), Arg::direction = (_direction * RAY_LENGTH)};

		std::vector<Line> rect_line_list;
		auto other_shape = other.getBoundingShape();
		if (auto other_rectf = std::get_if<RectF>(&other_shape))
		{
			rect_line_list.push_back(other_rectf->top());
			rect_line_list.push_back(other_rectf->right());
			rect_line_list.push_back(other_rectf->bottom());
			rect_line_list.push_back(other_rectf->left());
		}

		//交点を取得
		std::vector<Vec2> point_list;
		std::vector<int32> index_list;
		for (int32 i = 0; i < rect_line_list.size(); i++)
		{
			if (Optional<Vec2> optional_point = ray.intersectsAt(rect_line_list[i]))
			{
				if (optional_point.has_value())
				{
					point_list.push_back(optional_point.value());
					index_list.push_back(i);
				}
			}
		}

		//(良く分からないが)point_list,index_listの要素数が1のときは適当に反射
		if (point_list.size() == 0 or point_list.size() == 1)
		{
			_direction.y = -_direction.y;
			return;
		}

		//近さにより実際の接点を判定
		DirectionType reflect_face;
		auto dis0 = MathEx::distance(previous_rectf.center(), point_list[0]);
		auto dis1 = MathEx::distance(previous_rectf.center(), point_list[1]);
		if (dis0 <= dis1)
		{
			reflect_face = static_cast<DirectionType>(index_list[0]);
		}
		else
		{
			reflect_face = static_cast<DirectionType>(index_list[1]);
		}

		switch (reflect_face)
		{
		case Dir_Up:
			_direction.y = -_direction.y;
			break;
		case Dir_Right:
			_direction.x = -_direction.x;
			break;
		case Dir_Down:
			_direction.y = -_direction.y;
			break;
		case Dir_Left:
			_direction.x = -_direction.x;
			break;
		}
	}

	void penetrate()
	{
		//ぶつかった相手をリストで記憶し、collisionの範囲を抜けた段階でリストから排除する機構
	}

	void destroy()
	{
		if (_is_active)
		{
			std::shared_ptr<BulletParticle> ptr_bulletParticle = std::make_shared<BulletParticle>();
			ptr_bulletParticle->init(_rectf.center());
			God::getInstance().addIParticle(ptr_bulletParticle);
			_is_active = false;
		}
	}
};

Bullet::Bullet() : p_impl(std::make_shared<Impl>())
{
}

void Bullet::init(BulletContext bullet_context)
{
	p_impl->_rectf = bullet_context.rectf;
	p_impl->_direction = bullet_context.direction;
	p_impl->_owner_type = bullet_context.owner_type;
	p_impl->_speed = bullet_context.speed;
	p_impl->_range = bullet_context.range;
	p_impl->_damage = bullet_context.damage;
	p_impl->_reflection_count = bullet_context.reflection_count;
	p_impl->_penetration_count = bullet_context.penetration_count;
}


void Bullet::update(double delta_time)
{
	p_impl->move(delta_time);
}

void Bullet::draw() const
{
	p_impl->_rectf.draw(Palette::White);
}

std::variant<RectF, Circle> Bullet::getBoundingShape() const
{
	return p_impl->_rectf;
}

void Bullet::onCollision(const ICollidable& other)
{
	auto other_type = other.getType();
	switch (other_type)
	{
	case T_Player:
		if (p_impl->_owner_type == T_Enemy)
		{
			p_impl->destroy();
		}
		break;
	case T_Enemy:
		if (p_impl->_owner_type == T_Player)
		{
			p_impl->destroy();
		}
		break;
	case T_Block:
		{
			if (p_impl->_reflection_count > 0)
			{
				p_impl->reflect(other, p_impl->_reflection_count);
			}
			else
			{
				p_impl->destroy();
			}
		}
		break;
	case T_Bullet:
		break;
	default:
		break;
	}
}

ICollidableType Bullet::getType() const
{
	return T_Bullet;
}

bool Bullet::getIsActive() const
{
	return p_impl->_is_active;
}

int32 Bullet::getCollisionDamage() const
{
	return p_impl->_damage;
}

ICollidableType Bullet::getOwnerType() const
{
	return p_impl->_owner_type;
}
