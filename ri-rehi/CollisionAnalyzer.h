#pragma once
#include "ICollidable.h"

class CollisionAnalyzer
{
public:
	CollisionAnalyzer();
    void init();
    void draw() const;
    void update(double time_delta);

	void setTBlockCount(const int32 value);
	void setTPlayerCount(const int32 value);
	void setTBulletCount(const int32 value);
	void setTEnemyCount(const int32 value);

	int32 getTBlockCount() const;
	int32 getTPlayerCount() const;
	int32 getTBulletCount() const;
	int32 getTEnemyCount() const;

private:
    struct Impl;
    std::shared_ptr<Impl> p_impl;
};

