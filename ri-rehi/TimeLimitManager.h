#pragma once

class TimeLimitManager
{
public:
	TimeLimitManager();
	void init();
	void update(double delta_time);

	void reset();

	int32 getTimeLimitInt() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;

};
