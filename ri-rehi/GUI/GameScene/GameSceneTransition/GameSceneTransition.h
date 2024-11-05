#pragma once

class GameSceneTransition
{
public:
	GameSceneTransition();
	void init(double start_duration, double end_duration);
	void update(double delta_time);
	void draw() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
