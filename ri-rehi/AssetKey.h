#pragma once

namespace AssetKey
{
	constexpr StringView cursor = U"cursor";
	constexpr StringView liebesrechner_run = U"liebesrechner_run";
	constexpr StringView liebesrechner_stand = U"liebesrechner_stand";
	constexpr StringView exit = U"exit";
	constexpr StringView locked_exit = U"locked_exit";
	constexpr StringView slime = U"slime";
	constexpr StringView white_eye = U"white_eye";
	constexpr StringView ghost = U"ghost";
	constexpr StringView skelton = U"skelton";
	constexpr StringView sparkle = U"sparkle";
	constexpr StringView key = U"key";

	//Ability用のアイコン
	constexpr StringView icon_blank = U"icon_blank";
	constexpr StringView icon_bulletdamage = U"icon_bulletdamage";
	constexpr StringView icon_defence = U"icon_defence";
	constexpr StringView icon_hp = U"icon_hp";
	constexpr StringView icon_penetrate = U"icon_penetrate";
	constexpr StringView icon_reflection = U"icon_reflection";
	constexpr StringView icon_shot_interval = U"icon_shot_interval";
	constexpr StringView icon_sniper = U"icon_sniper";

	constexpr StringView bg_title = U"title";
	constexpr StringView bg_gameover = U"gameover";

	inline std::vector<StringView> ability_icon_name_list =
	{
		U"icon_blank",
		U"icon_bulletdamage",
		U"icon_defence",
		U"icon_hp",
		U"icon_penetrate",
		U"icon_reflection",
		U"icon_shot_interval",
		U"icon_sniper"
	};

	constexpr StringView pixel_b12 = U"pixel_b12";
	constexpr StringView pixel_b18 = U"pixel_b18";
	constexpr StringView pixel_b24 = U"pixel_b24";
	constexpr StringView pixel_b30 = U"pixel_b30";
	constexpr StringView pixel_b36 = U"pixel_b36";
	constexpr StringView pixel_b48 = U"pixel_b48";
	constexpr StringView pixel_b60 = U"pixel_b60";
	constexpr StringView pixel_b80 = U"pixel_b80";
	constexpr StringView pixel_b100 = U"pixel_b100";
	constexpr StringView pixel_b120 = U"pixel_b120";
	constexpr StringView pixel_b150 = U"pixel_b150";

	constexpr StringView ps_default = U"ps_default";
	constexpr StringView ps_grayscale = U"ps_grayscale";

	// constexpr StringView stage1 = U"resources/world/stage1.json";
	// constexpr StringView stage2 = U"resources/world/stage2.json";

	inline std::vector<StringView> getStages()
	{
		return {
			U"resources/world/stage0.json",
			U"resources/world/stage1.json",
			U"resources/world/stage2.json",
			U"resources/world/stage3.json",
			U"resources/world/stage4.json",
			U"resources/world/stage5.json",
			U"resources/world/stage6.json",
			U"resources/world/stage7.json",
			U"resources/world/stage8.json",
			U"resources/world/stage9.json",
			U"resources/world/stage10.json",
			U"resources/world/stage11.json",
			U"resources/world/stage12.json",
			U"resources/world/stage13.json",
			U"resources/world/stage14.json",
			U"resources/world/stage15.json",
		};
	}
}
