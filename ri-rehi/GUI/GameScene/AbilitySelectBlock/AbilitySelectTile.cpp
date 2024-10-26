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

	Vec2 _title_pos;
	String _title_string;

	Vec2 _icon_pos;
	AssetName _icon_large_assetname;

	Vec2 _description_pos;
	std::vector<String> _description_list;
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
	p_impl->_title_string = U"HogeHoge";
	p_impl->_icon_large_assetname = U"liebesrechner_stand";
	p_impl->_description_list = { U"Description 1", U"Description 2", U"Description 3" };
}

void AbilitySelectTile::update(double delta_time)
{
	auto rolled_ability = God::getInstance().getPtrAbilityManager()->getRolledAbilityList()[p_impl->_index];
	p_impl->_title_string = rolled_ability.getTitle();
	p_impl->_icon_large_assetname = rolled_ability.getIconLargeAssetName();
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
	if(p_impl->_rectf.mouseOver())
	{
		p_impl->_rectf.draw(Palette::Black).drawFrame(p_impl->_rectf_mouseover_thickness, Palette::White);
	}
	else
	{
		p_impl->_rectf.draw(Palette::Black).drawFrame(p_impl->_rectf_thickness, Palette::White);
	}

	auto title_rect = FontAsset(U"pixel_b48")(p_impl->_title_string).draw(p_impl->_title_pos);
	auto icon_rect = TextureAsset(p_impl->_icon_large_assetname).draw(p_impl->_icon_pos );

	std::vector<RectF> desc_rects;
	for(int i = 0; i < p_impl->_description_list.size(); i++)
	{
		auto desc_rect = FontAsset(AssetKey::pixel_b36)(p_impl->_description_list[i]).draw(p_impl->_description_pos);
		desc_rects.push_back(desc_rect);
	}

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
