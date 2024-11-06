﻿#pragma once
#include "IParticle.h"

class SparkleParticle :public IParticle
{
public:
	SparkleParticle();
	void init(Vec2 pos);
	bool update(double delta_time, double accumulated_time) override;
	void draw() const override;
	double getAccumulatedTime() const override;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
