#include "stdafx.h"
#include "TimeLimitManager.h"

struct TimeLimitManager::Impl
{
	double _time_left = 120;
	double _time_limit = 120;

	int32 _time_limit_int = 120;
};

TimeLimitManager::TimeLimitManager() : p_impl(std::make_shared<Impl>())
{
}

void TimeLimitManager::init()
{
	p_impl->_time_left = p_impl->_time_limit;
}

void TimeLimitManager::update(double delta_time)
{
	p_impl->_time_left -= delta_time;
	p_impl->_time_limit_int = Math::Floor(p_impl->_time_left);

	if(p_impl->_time_limit_int < 0)
	{
		p_impl->_time_limit_int = 0;
	}
}

void TimeLimitManager::reset()
{
	p_impl->_time_left = p_impl->_time_limit;
}

int32 TimeLimitManager::getTimeLimitInt() const
{
	return p_impl->_time_limit_int;
}
