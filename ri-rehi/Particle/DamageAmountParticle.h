#pragma once
#include "IParticle.h"

class DamageAmountParticle : public IParticle
{
public:
	DamageAmountParticle();
	void init(Vec2 pos, int32 damage_amount);
	bool update(double delta_time, double accumulated_time) override;
	void draw() const override;
	double getAccumulatedTime() const override;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
