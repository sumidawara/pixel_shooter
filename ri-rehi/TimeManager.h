#pragma once

class TimeManager
{
public:
	TimeManager();
	void init();
	void update(double delta_time);
	void draw();

	void setGameTimeScale(double value);
	void setIsManuallyPaused(bool value);
	void setIsForciblyPaused(bool value);

	double getGameTimeScale() const;
	double getSystemTimeScale() const;

	bool getIsManuallyPaused() const;
	bool getIsForciblyPaused() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
