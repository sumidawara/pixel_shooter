#include "stdafx.h"
#include "AbilitySummary.h"

#include "God.h"

struct AbilitySummary::Impl
{
	Vec2 _pos;

	int32 _icon_columns = 10;
	double _icon_interval = 40;
	double _icon_frame_thickness = 1;

	int32 _icon_count;
	std::vector<ColorF> _icon_frame_color_list;
	std::vector<String> _icon_small_assetname_list;

	String appendSmallSuffix(StringView str)
	{
		return String(str) + U"_small";
	}
};

AbilitySummary::AbilitySummary() : p_impl(std::make_shared<Impl>())
{
}

void AbilitySummary::init(Vec2 pos)
{
	p_impl->_pos = pos;
}

void AbilitySummary::update(double delta_time)
{
	auto achieved_ability_list = God::getInstance().getPtrAbilityManager()->getAchievedAbilityList();
	p_impl->_icon_count = achieved_ability_list.size();

	p_impl->_icon_small_assetname_list.clear();
	p_impl->_icon_frame_color_list.clear();
	for(int32 i = 0; i < p_impl->_icon_count; i++)
	{
		p_impl->_icon_small_assetname_list.push_back(p_impl->appendSmallSuffix(achieved_ability_list[i].getIconAssetName()));
		p_impl->_icon_frame_color_list.push_back(GraphicSetting::rarity2ColorF(achieved_ability_list[i].getRarity()));
	}
}

void AbilitySummary::draw() const
{
	for (int32 i = 0; i < p_impl->_icon_count; i++)
	{
		auto icon_pos = p_impl->_pos + Vec2{p_impl->_icon_interval, 0.0} * i;
		auto rect = TextureAsset(p_impl->_icon_small_assetname_list[i]).draw(icon_pos);
		rect.drawFrame(p_impl->_icon_frame_thickness, p_impl->_icon_frame_color_list[i]);
	}
}
