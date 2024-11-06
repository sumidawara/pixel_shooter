#pragma once
class HPBar
{
public:
	HPBar();

	void init(const RectF& rectf);

	void update(double delta_time);
	void draw() const;

	Vec2 getPos() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};

