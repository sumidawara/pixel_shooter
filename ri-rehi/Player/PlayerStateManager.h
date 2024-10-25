#pragma once
#include "PlayerState.h"

class PlayerStateManager
{
public:
	PlayerStateManager();
	void init();
	void update(double delta_time);
	void draw() const;

	void enhancePlayerState(const PlayerState& player_state);
	void addExp(int32 value);

	void setCurrentHP(int32 value);
	void setIsInvincible(bool value);

	int32 getRemainingExpToNextLevelUp() const;

	PlayerState getPlayerState() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
