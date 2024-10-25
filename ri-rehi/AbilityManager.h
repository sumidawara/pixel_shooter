#pragma once
#include "Ability.h"

class AbilityManager
{
public:
	AbilityManager();
	void init();
	void update(double delta_time);
	void draw();

	void rollAbility();
	void addAbility(int32 index);

	std::vector<Ability>& getRolledAbilityList() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;

};
