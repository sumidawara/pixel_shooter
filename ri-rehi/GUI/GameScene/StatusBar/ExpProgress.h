#pragma once

class ExpProgress
{
public:
	ExpProgress();
	void init(Vec2 pos);
	void update(double delta_time);
	void draw() const;

	void setRemainingExpToNextLevelUp(int32 value);

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
