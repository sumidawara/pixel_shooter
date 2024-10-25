#pragma once
#include "ExpProgress.h"

class ExpBlock
{
public:
	ExpBlock();
	void init(Vec2 pos);
	void update(double delta_time);
	void draw() const;

	void setLevel(int32 value);
	void setRemainingExpToNextLevelUp(int32 value);

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
