#include "stdafx.h"
#include "GameSceneTransition.h"

#include "Debug.h"
#include "God.h"

struct GameSceneTransition::Impl
{
	double _start_duration;
	double _end_duration;

	GameSceneTransitionType::State _state = GameSceneTransitionType::None;
	double _starting_accumulated_time = 0.0;
	double _ending_accumulated_time = 0.0;
	double _starting_t = 0.0;
	double _ending_t = 0.0;

	void updateAccumulatedTime(double delta_time)
	{
		_state = God::getInstance().getPtrGameSceneGUIManager()->getTransitionState();
		if (_state == GameSceneTransitionType::Starting)
		{
			_starting_accumulated_time += delta_time;
			if (_starting_accumulated_time < _start_duration)
			{
				_starting_t = _starting_accumulated_time / _start_duration;
			}
			else
			{
				//GUIのくせに内部状態を変更
				God::getInstance().getPtrGameSceneGUIManager()->setTransitionState(GameSceneTransitionType::Ending);
			}
		}
		else if (_state == GameSceneTransitionType::Ending)
		{
			_ending_accumulated_time += delta_time;
			if (_ending_accumulated_time < _end_duration)
			{
				_ending_t = _ending_accumulated_time / _end_duration;
			}
			else
			{
				_starting_accumulated_time = 0.0;
				_ending_accumulated_time = 0.0;
				_starting_t = 0.0;
				_ending_t = 0.0;

				//GUIのくせに内部状態を変更
				God::getInstance().getPtrGameSceneGUIManager()->setTransitionState(GameSceneTransitionType::None);
			}
		}
	}

	void drawFadeIn(double t) const
	{
		Vec2 pos = {0, 0};
		Vec2 size = { t * Scene::Size().x, Scene::Size().y};
		RectF fade_in_background = {pos, size};

		fade_in_background.draw(Palette::Black);
	}

	void drawFadeOut(double t) const
	{
		Vec2 pos = {0, 0};
		Vec2 size = { (1 - t) * Scene::Size().x, Scene::Size().y};
		RectF fade_in_background = {pos, size};

		fade_in_background.draw(Palette::Black);
	}
};

GameSceneTransition::GameSceneTransition() : p_impl(std::make_shared<Impl>())
{
}

void GameSceneTransition::init(double start_duration, double end_duration)
{

	p_impl->_start_duration = start_duration;
	p_impl->_end_duration = end_duration;
}

void GameSceneTransition::update(double delta_time)
{
	//Debug::getInstance().writeline(0, U"GameSceneTransitionType : " + Format(p_impl->_state));
	p_impl->updateAccumulatedTime(delta_time);
}

void GameSceneTransition::draw() const
{
	if (p_impl->_state == GameSceneTransitionType::Starting)
	{
		p_impl->drawFadeIn(p_impl->_starting_t);
	}
	if (p_impl->_state == GameSceneTransitionType::Ending)
	{
		p_impl->drawFadeOut(p_impl->_ending_t);
	}
}
