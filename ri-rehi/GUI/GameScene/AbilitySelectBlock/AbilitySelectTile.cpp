#include "stdafx.h"
#include "AbilitySelectTile.h"

#include "AssetKey.h"
#include "DebugSetting.h"
#include "God.h"

struct AbilitySelectTile::Impl
{
	RectF _rectf;
	double _rectf_thickness = 4;
	double _rectf_mouseover_thickness = 12;

	int32 _index;
	int32 _rarity;

	Vec2 _title_pos;
	String _title_string;

	Vec2 _icon_pos;
	AssetName _icon_large_assetname;

	Vec2 _description_pos;
	std::vector<String> _description_list;

	String appendLargeSuffix(StringView str)
	{
		return String(str) + U"_large";
	}
};

AbilitySelectTile::AbilitySelectTile() : p_impl(std::make_shared<Impl>())
{
}

void AbilitySelectTile::init(Vec2 pos, int32 index)
{
	auto size = Vec2{400, 650};
	auto rectf = RectF{pos, size};
	p_impl->_rectf = rectf;

	double LEFT_PADDING = 40;

	auto title_pos = pos + Vec2{LEFT_PADDING, 40};
	p_impl->_title_pos = title_pos;

	auto icon_pos = pos + Vec2(72, 130);
	p_impl->_icon_pos = icon_pos;

	auto description_pos = pos + Vec2(LEFT_PADDING, 410);
	p_impl->_description_pos = description_pos;

	p_impl->_index = index;
}

void AbilitySelectTile::update(double delta_time)
{
	//abilityのパラメーターを渡す
	auto rolled_ability = God::getInstance().getPtrAbilityManager()->getRolledAbilityList()[p_impl->_index];
	p_impl->_title_string = rolled_ability.getTitle();
	p_impl->_rarity = rolled_ability.getRarity();
	p_impl->_icon_large_assetname = p_impl->appendLargeSuffix(rolled_ability.getIconAssetName());
	p_impl->_description_list = rolled_ability.getDescriptionList();

	//クリック判定
	auto is_input_locked = God::getInstance().getPtrGameSceneGUIManager()->getIsInputLock();
	if(p_impl->_rectf.leftClicked() and not is_input_locked)
	{
		God::getInstance().getPtrGameSceneGUIManager()->onAbilitySelectTileClicked(p_impl->_index);
	}
}

void AbilitySelectTile::draw()
{
	auto rarity_color = GraphicSetting::rarity2ColorF(p_impl->_rarity);

	//背景と外枠の描画
	if(p_impl->_rectf.mouseOver())
	{
		p_impl->_rectf.draw(Palette::Black).drawFrame(p_impl->_rectf_mouseover_thickness, rarity_color);
	}
	else
	{
		p_impl->_rectf.draw(Palette::Black).drawFrame(p_impl->_rectf_thickness, rarity_color);
	}

	//タイトルの描画
	auto title_rect = FontAsset(U"pixel_b48")(p_impl->_title_string).draw(p_impl->_title_pos);

	//アイコンの描画
	auto icon_rect = TextureAsset(p_impl->_icon_large_assetname).draw(p_impl->_icon_pos );

	//descriptionの描画
	std::vector<RectF> desc_rects;
	auto description_pos = p_impl->_description_pos;
	for(int i = 0; i < p_impl->_description_list.size(); i++)
	{
		auto desc_rect = FontAsset(AssetKey::pixel_b36)(p_impl->_description_list[i]).draw(p_impl->_description_pos);
		desc_rects.push_back(desc_rect);
	}

	//デバッグ用
	if(DebugSetting::getIsGuiDebuggingVisible())
	{
		title_rect.draw(DebugSetting::getGuiDebugColor());
		icon_rect.draw(DebugSetting::getGuiDebugColor());
		for(auto& desc_rect : desc_rects)
		{
			desc_rect.draw(DebugSetting::getGuiDebugColor());
		}
	}
}

RectF AbilitySelectTile::getRectF() const
{
	return p_impl->_rectf;
}
