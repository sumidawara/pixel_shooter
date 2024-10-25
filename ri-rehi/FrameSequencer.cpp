#include "stdafx.h"
#include "FrameSequencer.h"

FrameSequencer::FrameSequencer(int32 interval_frame, int32 max_index_count)
	:
	_interval_frame(interval_frame),
	_interval_time(interval_frame / 60.0),
	_max_index_count(max_index_count)
{
}

void FrameSequencer::update(double delta_time)
{
	_accumulated_time += delta_time;

	if (_interval_time < _accumulated_time)
	{
		_current_index++;
		_current_index %= _max_index_count;

		_accumulated_time -= _interval_time;
	}
}

void FrameSequencer::reset()
{
	_current_index = 0.0;
	_accumulated_time = 0.0;
}

int32 FrameSequencer::getCurrentIndex() const
{
	return _current_index;
}
