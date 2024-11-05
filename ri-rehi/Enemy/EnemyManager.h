#pragma once
#include "Enum.h"

class EnemyManager
{
public:
	EnemyManager();
	void init();
	void update(double delta_time);
	void draw() const;

	void clearEnemy();

	void createEnemy(EnemyType::EnemyType enemy_type, Vec2 pos);
	void giveKeyToOneEnemy();

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
