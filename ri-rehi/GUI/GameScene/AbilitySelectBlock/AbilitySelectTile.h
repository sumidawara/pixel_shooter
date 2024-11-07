#pragma once

class AbilitySelectTile
{
public:
	AbilitySelectTile();
	void init(Vec2 pos, int32 index);
	void update(double delta_time);
	void draw() const;

	RectF getRectF() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
