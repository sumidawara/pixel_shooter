#pragma once

namespace AssetKey
{
	constexpr StringView cursor = U"cursor";
	constexpr StringView liebesrechner_run = U"liebesrechner_run";
	constexpr StringView liebesrechner_stand = U"liebesrechner_stand";
	constexpr StringView exit = U"exit";
	constexpr StringView locked_exit = U"locked_exit";
	constexpr StringView slime = U"slime";

	constexpr StringView pixel_b12 = U"pixel_b12";
	constexpr StringView pixel_b18 = U"pixel_b18";
	constexpr StringView pixel_b24 = U"pixel_b24";
	constexpr StringView pixel_b30 = U"pixel_b30";
	constexpr StringView pixel_b36 = U"pixel_b36";
	constexpr StringView pixel_b48 = U"pixel_b48";
	constexpr StringView pixel_b60 = U"pixel_b60";
	constexpr StringView pixel_b80 = U"pixel_b80";

	constexpr StringView ps_default = U"ps_default";

	// constexpr StringView stage1 = U"resources/world/stage1.json";
	// constexpr StringView stage2 = U"resources/world/stage2.json";

	inline std::vector<StringView> getStages()
	{
		return {
			U"resources/world/stage0.json",
			U"resources/world/stage1.json",
			U"resources/world/stage2.json"
		};
	}
}
