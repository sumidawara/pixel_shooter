#pragma once
#include "IEnemyBehavior.h"

class WanderBehavior : public IEnemyBehavior
{
public:
	void execute(MobAIContext& mob_ai_context, double delta_time) override;

private:
	double WANDERING_THRESHOLD_TIME = 3;
	double _accumulated_time = 0;
};

