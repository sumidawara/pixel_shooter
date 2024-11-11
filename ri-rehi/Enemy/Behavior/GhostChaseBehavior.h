#pragma once
#include "IEnemyBehavior.h"

class GhostChaseBehavior : public IEnemyBehavior
{
public:
	void execute(MobAIContext& mob_ai_context, double delta_time) override;

};
