#include "stdafx.h"
#include "DamageAmountParticle.h"

#include "DebugSetting.h"

struct DamageAmountParticle::Impl
{
	Vec2 _pos;
	Vec2 _offset = {3, 3};
	Vec2 _speed = {0, -100};
	double _life_time = 0.2;
	double _accumulated_time = 0.0;

	int32 _damage_amount;
};

DamageAmountParticle::DamageAmountParticle() : p_impl(std::make_shared<Impl>())
{
}

void DamageAmountParticle::init(Vec2 pos, int32 damage_amount)
{
	p_impl->_pos = pos;
	p_impl->_damage_amount = damage_amount;
}

bool DamageAmountParticle::update(double delta_time, double accumulated_time)
{
	p_impl->_accumulated_time = accumulated_time;

	p_impl->_pos += delta_time * p_impl->_speed;

	return (accumulated_time < p_impl->_life_time);
}

void DamageAmountParticle::draw() const
{
	String str = Format(p_impl->_damage_amount);
	auto black_rect = FontAsset(U"pixel_b24")(str).drawAt(p_impl->_pos + p_impl->_offset, Palette::Black);
	auto white_rect = FontAsset(U"pixel_b24")(str).drawAt(p_impl->_pos, Palette::White);

	if(DebugSetting::getIsParticleRectVisible())
	{
		black_rect.draw(DebugSetting::getParticleColor());
		white_rect.draw(DebugSetting::getParticleColor());
	}
}

double DamageAmountParticle::getAccumulatedTime() const
{
	return p_impl->_accumulated_time;
}
