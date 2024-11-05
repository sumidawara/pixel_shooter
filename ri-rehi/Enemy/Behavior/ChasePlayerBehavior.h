#pragma once
#include "IEnemyBehavior.h"
#include "MobAIContext.h"

class ChasePlayerBehavior : public IEnemyBehavior
{
public:
	void execute(MobAIContext& mob_ai_context, double delta_time) override;

private:
};

