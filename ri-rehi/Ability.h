#pragma once
#include "AbilityContext.h"

class Ability
{
public:
	Ability();
	void init(const String& title, const AssetName& icon_large_assetname, const std::vector<String>& description_list);
	void init(AbilityContext ability_context);
	void update(double delta_time);
	void draw();

	void writeline(int32 writeline_index) const;

	int32 getId() const;
	PlayerState getParameter() const;
	std::vector<int> getRequiredIdList() const;

	const String& getTitle() const;
	const AssetName& getIconLargeAssetName() const;
	const std::vector<String>& getDescriptionList() const;

private:
	struct Impl;
	std::shared_ptr<Impl> p_impl;
};
