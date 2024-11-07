#pragma once
#include "Player/PlayerState.h"

struct AbilityContext
{
	int32 id;
	int32 rarity;
	std::vector<int32> required_id_list;
	PlayerState parameter;

	String title;
	AssetName icon_large_assetname;
	std::vector<String> description_list;
};
