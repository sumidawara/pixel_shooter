#pragma once

class AbilitySelectBlock
{
public:
	AbilitySelectBlock();
	void init(Vec2 pos);
	void update(double delta_time);
	void draw();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;

};
