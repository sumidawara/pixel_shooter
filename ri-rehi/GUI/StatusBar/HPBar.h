#pragma once
class HPBar
{
public:
	HPBar();

	void init(RectF rectf, int32 current_hp, int32 max_hp);

	void update(double delta_time);
	void draw() const;

	Vec2 getPos() const;

	void setHP(int32 current_hp, int32 max_hpe);

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

