#include "stdafx.h"
#include "TimeManager.h"

struct TimeManager::Impl
{
	double _game_timescale = 1.0;
	double _system_timescale = 1.0;

	double _is_manually_paused = false;
	double _is_forcibly_paused = false;
};

TimeManager::TimeManager() : p_impl(std::make_shared<Impl>())
{
}

void TimeManager::init()
{

}

void TimeManager::update(double delta_time)
{

}

void TimeManager::draw()
{
}

void TimeManager::setGameTimeScale(double value)
{
	p_impl->_game_timescale = value;
}

void TimeManager::setIsManuallyPaused(bool value)
{
	p_impl->_is_manually_paused = value;
}

void TimeManager::setIsForciblyPaused(bool value)
{
	p_impl->_is_forcibly_paused = value;
}

double TimeManager::getGameTimeScale() const
{
	return p_impl->_game_timescale;
}

double TimeManager::getSystemTimeScale() const
{
	return p_impl->_system_timescale;
}

bool TimeManager::getIsManuallyPaused() const
{
	return p_impl->_is_manually_paused;
}

bool TimeManager::getIsForciblyPaused() const
{
	return p_impl->_is_forcibly_paused;
}
