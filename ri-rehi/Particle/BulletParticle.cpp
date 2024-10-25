#include "stdafx.h"
#include "BulletParticle.h"

#include "DebugSetting.h"

struct BulletParticle::Impl
{
	Vec2 _pos;
	double _life_time = 0.2;
	double _accumulated_time = 0.0;

	struct Debris
	{
		RectF rectf;
		Vec2 dir;
		double speed;
	};

	std::vector<Debris> _debris_list;
};

BulletParticle::BulletParticle() : p_impl(std::make_shared<Impl>())
{
}


void BulletParticle::init(Vec2 pos)
{
	p_impl->_pos = pos;
	for (int32 i = 0; i < 8; i++)
	{
		RectF rectf{ Arg::center_<Vec2>(pos), 10, 10 };
		Vec2 randVec{ Random<double>(-1.0, 1.0), Random<double>(-1.0, 1.0) };
		double randSpeed = Random<double>(200.0, 300.0);
		p_impl->_debris_list.push_back(Impl::Debris{ rectf, randVec.normalize(), randSpeed});
	}
}

bool BulletParticle::update(double delta_time, double accumulated_time)
{
	p_impl->_accumulated_time = accumulated_time;

	for (auto& debris : p_impl->_debris_list)
	{
		Vec2 newPos = p_impl->_pos + debris.dir * debris.speed * accumulated_time;
		debris.rectf.setCenter(newPos);
	}

	return (accumulated_time < p_impl->_life_time);
}

void BulletParticle::draw() const
{
	for (auto& debris : p_impl->_debris_list)
	{
		debris.rectf.draw(Palette::White);

		if(DebugSetting::getIsParticleRectVisible()) debris.rectf.draw(DebugSetting::getParticleColor());
	}
}

double BulletParticle::getAccumulatedTime() const
{
	return p_impl->_accumulated_time;
}
