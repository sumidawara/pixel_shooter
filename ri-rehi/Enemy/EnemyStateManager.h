#pragma once
#include "EnemyState.h"

class EnemyStateManager
{
public:
	EnemyStateManager();
	void init(const EnemyState& enemy_state, int32 level);
	void update(double delta_time);
	void draw() const;

	void onDamaged(int32 received_damage);

	EnemyState getEnemyState();

	void setRectf(const RectF& rectf);
	void setDirection(Vec2 direction);
	void setHasKey(bool has_key);

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
