#pragma once
#include "IEnemyBehavior.h"

class GridChaseBehavior: public IEnemyBehavior
{
public:
	void execute(MobAIContext& mob_ai_context, double delta_time) override;

private:
	struct AdjacentBlock;
	Point previous_dir = {-999, -999};
};
