#pragma once
#include "MobAIContext.h"

class IEnemyBehavior
{
public:
	virtual ~IEnemyBehavior() = default;
	virtual void execute(MobAIContext& mob_ai_context, double delta_time) = 0;

private:
};

