#include "stdafx.h"
#include "KeyGetParticle.h"

#include "AssetKey.h"
#include "DebugSetting.h"
#include "God.h"
#include "MathEx.h"
#include "SparkleParticle.h"

struct KeyGetParticle::Impl
{
	Vec2 _pos;
	Vec2 _start_pos;
	Vec2 _end_pos;
	Vec2 _start_relative_pos = {0, 0};
	Vec2 _end_relative_pos = {0, -90};

	Vec2 _key_pos;
	Vec2 _key_relative_pos = {-25, 0};

	Vec2 _text_pos;
	Vec2 _text_relative_pos = {35, 0};

	//sparkle
	double _inner_circle_range = 30;
	double _outer_circle_range = 60;

	Vec2 _speed = {0, -100};

	double _life_time = 0.8;
	double _accumulated_time = 0.0;

	void generateSparkle()
	{
		double random_distance = Random(_inner_circle_range, _outer_circle_range);
		double angle = Random(0.0, 2 * Math::Pi);
		double x = _key_pos.x + random_distance * Math::Cos(angle);
		double y = _key_pos.y + random_distance * Math::Sin(angle);

		//キラキラパーティクル
		auto ptr_sparkle_particle = std::make_shared<SparkleParticle>();
		ptr_sparkle_particle->init(Vec2{x, y});
		God::getInstance().getPtrParticleManager()->addParticleOnNextFrame(ptr_sparkle_particle);
	}
};

KeyGetParticle::KeyGetParticle() : p_impl(std::make_shared<Impl>())
{
}

void KeyGetParticle::init(Vec2 pos)
{
	p_impl->_pos = pos;
	p_impl->_start_pos = pos + p_impl->_start_relative_pos;
	p_impl->_end_pos = pos + p_impl->_end_relative_pos;

	p_impl->_key_pos = pos + p_impl->_key_relative_pos;
	p_impl->_text_pos = pos + p_impl->_text_relative_pos;
}

bool KeyGetParticle::update(double delta_time, double accumulated_time)
{
	p_impl->_accumulated_time = accumulated_time;

	auto t = accumulated_time / p_impl->_life_time;
	auto e = EaseInOut(Easing::Quad, t);

	//座標更新
	auto pos = MathEx::lerp(p_impl->_start_pos, p_impl->_end_pos, e);
	p_impl->_pos = pos;
	p_impl->_key_pos = pos + p_impl->_key_relative_pos;
	p_impl->_text_pos = pos + p_impl->_text_relative_pos;

	p_impl->generateSparkle();

	return (accumulated_time < p_impl->_life_time);
}

void KeyGetParticle::draw() const
{
	auto key_rect = TextureAsset(AssetKey::key).drawAt(p_impl->_key_pos);
	auto text_rect = FontAsset(AssetKey::pixel_b30)(U"GET").drawAt(p_impl->_text_pos, GraphicSetting::getYELLOW());

	if(DebugSetting::getIsParticleRectVisible())
	{
		key_rect.draw(DebugSetting::getParticleColor());
		text_rect.draw(DebugSetting::getParticleColor());
	}
}

double KeyGetParticle::getAccumulatedTime() const
{
	return p_impl->_accumulated_time;
}
