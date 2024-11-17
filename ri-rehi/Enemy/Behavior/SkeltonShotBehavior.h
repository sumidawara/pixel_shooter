#pragma once
#include "IEnemyBehavior.h"

class SkeltonShotBehavior : public IEnemyBehavior
{
public:
	void execute(MobAIContext& mob_ai_context, double delta_time) override;

private:
	double SHOT_THRESHOLD_TIME = 0.5;
	double shot_accumulated_time = 0;
};
