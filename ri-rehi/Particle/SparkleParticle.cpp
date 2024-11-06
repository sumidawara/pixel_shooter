#include "stdafx.h"
#include "SparkleParticle.h"

#include "AssetKey.h"

struct SparkleParticle::Impl
{
	Vec2 _pos;
	int32 _anime_index = 0;

	double _one_third_boundary;
	double _two_third_boundary;

	double _life_time = 0.3;
	double _accumulated_time = 0.0;

	void calcAnimeIndex(double accumulated_time)
	{
		if(accumulated_time < _one_third_boundary)
		{
			_anime_index = 0;
		}
		if(_one_third_boundary <= accumulated_time && accumulated_time < _two_third_boundary)
		{
			_anime_index = 1;
		}
		if(_two_third_boundary <= accumulated_time)
		{
			_anime_index = 2;
		}
	}
};

SparkleParticle::SparkleParticle() : p_impl(std::make_shared<Impl>())
{
}

void SparkleParticle::init(Vec2 pos)
{
	p_impl->_pos = pos;

	p_impl->_one_third_boundary = p_impl->_life_time / 3.0;
	p_impl->_two_third_boundary = p_impl->_life_time / 3.0 * 2.0;
}

bool SparkleParticle::update(double delta_time, double accumulated_time)
{
	p_impl->_accumulated_time = accumulated_time;

	p_impl->calcAnimeIndex(accumulated_time);

	return (accumulated_time < p_impl->_life_time);
}

void SparkleParticle::draw() const
{
	TextureAsset(AssetKey::sparkle)(p_impl->_anime_index * 20, 0, 20, 20).drawAt(p_impl->_pos);
}

double SparkleParticle::getAccumulatedTime() const
{
	return p_impl->_accumulated_time;
}
