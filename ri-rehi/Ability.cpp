#include "stdafx.h"
#include "Ability.h"

#include "Debug.h"
#include "Player/PlayerState.h"

struct Ability::Impl
{
	int32 _id;
	std::vector<int32> _required_id_list;
	PlayerState _parameter;

	//AbilitySelectTileに表示させる
	String _title;
	AssetName _icon_large_assetname;
	std::vector<String> _description_list;
};

Ability::Ability() : p_impl(std::make_shared<Impl>())
{
}

void Ability::init(const String& title, const AssetName& icon_large_assetname, const std::vector<String>& description_list)
{
	p_impl->_title = title;
	p_impl->_icon_large_assetname = icon_large_assetname;
	p_impl->_description_list = description_list;
}

void Ability::init(AbilityContext ability_context)
{
	p_impl->_id = ability_context.id;
	p_impl->_required_id_list = ability_context.required_id_list;
	p_impl->_parameter = ability_context.parameter;

	p_impl->_title = ability_context.title;
	p_impl->_icon_large_assetname = ability_context.icon_large_assetname;
	p_impl->_description_list = ability_context.description_list;
}

void Ability::update(double delta_time)
{
}

void Ability::draw()
{
}

void Ability::writeline(int32 writeline_index) const
{
	if(Debug::getInstance().getDebugScreenIndex() == writeline_index)
	{
		int32 i = writeline_index;

		Debug::getInstance().writeline(i, U"title : " + Format(p_impl->_title));
		Debug::getInstance().writeline(i);
	}
}

int32 Ability::getId() const
{
	return p_impl->_id;
}

PlayerState Ability::getParameter() const
{
	return p_impl->_parameter;
}

std::vector<int> Ability::getRequiredIdList() const
{
	return p_impl->_required_id_list;
}

const String& Ability::getTitle() const
{
	return p_impl->_title;
}

const AssetName& Ability::getIconLargeAssetName() const
{
	return p_impl->_icon_large_assetname;
}

const std::vector<String>& Ability::getDescriptionList() const
{
	return p_impl->_description_list;
}
