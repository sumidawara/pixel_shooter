﻿#pragma once

class HPBlock
{
public:
	HPBlock();
	void init(Vec2 pos);
	void update(double delta_time);
	void draw() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
