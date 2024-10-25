#pragma once
class FrameSequencer
{
//24フレーム間隔で4コマ : FrameSequencer(24, 4);
public:
	FrameSequencer(int32 interval_frame, int32 max_index_count);

	void update(double delta_time);
	void reset();

	int32 getCurrentIndex() const;

private:
	int32 _interval_frame;

	int32 _current_index = 0;
	int32 _max_index_count;

	double _interval_time;
	double _accumulated_time = 0.0;
	

};

