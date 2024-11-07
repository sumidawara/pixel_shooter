#pragma once
#include "Ability.h"

class AbilityManager
{
public:
	AbilityManager();
	void init();
	void update(double delta_time);
	void draw() const;

	void rollAbility();
	void addAbilityFromRollAbilityList(int32 index);

	std::vector<Ability>& getRolledAbilityList() const;
	std::vector<Ability>& getAchievedAbilityList() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;

};
