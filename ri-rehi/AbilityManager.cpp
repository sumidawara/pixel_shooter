#include "stdafx.h"
#include "AbilityManager.h"

#include "Ability.h"
#include "AbilityContext.h"
#include "Debug.h"
#include "God.h"
#include "MathEx.h"

struct AbilityManager::Impl
{
	std::vector<Ability> _all_ability_list;
	std::vector<Ability> _achieved_ability_list;
	std::vector<Ability> _rolled_ability_list;

	std::vector<int32> _achieved_id_list;

	int32 _writeline_index = 5;

	void loadAbilityJson(FilePath path)
	{
		const JSON json = JSON::Load(path);


		for (const auto& raw_ability : json[U"abilities"].arrayView())
		{
			AbilityContext context;
			context.id = raw_ability[U"id"].get<int32>();
			context.title = raw_ability[U"title"].get<String>();
			context.icon_large_assetname = raw_ability[U"icon_large_assetname"].get<String>();
			for(const auto& raw_required_id : raw_ability[U"required_id"].arrayView())
			{
				int32 required_id = raw_required_id.get<int32>();
				context.required_id_list.push_back(required_id);
			}
			for(const auto& raw_description : raw_ability[U"description_list"].arrayView())
			{
				String description = raw_description.get<String>();
				context.description_list.push_back(description);
			}
			for(const auto& raw_parameter : raw_ability[U"parameter"].arrayView())
			{
				if(raw_parameter.contains(U"max_hp"))
				{
					context.parameter.max_hp = raw_parameter[U"max_hp"].get<int32>();
				}
				if(raw_parameter.contains(U"defence"))
				{
					context.parameter.defence = raw_parameter[U"defence"].get<int32>();
				}
				if(raw_parameter.contains(U"ranged_damage"))
				{
					context.parameter.ranged_damage = raw_parameter[U"ranged_damage"].get<int32>();
				}
			}

			Ability ability;
			ability.init(context);
			_all_ability_list.push_back(ability);
		}
	}

	void writeline()
	{
		if(Debug::getInstance().getDebugScreenIndex() == _writeline_index)
		{
			int32 i = _writeline_index;
			Debug::getInstance().writeline(i, U"_all_ability_list.size() : " + Format(_all_ability_list.size()));
			Debug::getInstance().writeline(i);

			Debug::getInstance().writeline(i, U"all_ability_list");
			for(const auto& ability : _all_ability_list)
			{
				Debug::getInstance().writeline(i, U"title : " + ability.getTitle());
			}
			Debug::getInstance().writeline(i);

			Debug::getInstance().writeline(i, U"achieved_ability_list");
			for(const auto& ability : _achieved_ability_list)
			{
				Debug::getInstance().writeline(i, U"title : " + ability.getTitle());
			}
			Debug::getInstance().writeline(i);
		}
	}
};

AbilityManager::AbilityManager() : p_impl(std::make_shared<Impl>())
{
}

void AbilityManager::init()
{
	p_impl->loadAbilityJson(U"resources/ability/ability.json");
}

void AbilityManager::update(double delta_time)
{
	p_impl->writeline();
}

void AbilityManager::draw()
{
}

void AbilityManager::rollAbility()
{
	p_impl->_rolled_ability_list.clear();

	auto random_index_triplet = MathEx::generateUniqueRandomNumbers(0, p_impl->_all_ability_list.size() - 1, 3);
	p_impl->_rolled_ability_list.push_back(p_impl->_all_ability_list[random_index_triplet[0]]);
	p_impl->_rolled_ability_list.push_back(p_impl->_all_ability_list[random_index_triplet[1]]);
	p_impl->_rolled_ability_list.push_back(p_impl->_all_ability_list[random_index_triplet[2]]);

	God::getInstance().getPtrTimeManager()->setIsForciblyPaused(true);
	God::getInstance().getPtrGameSceneGUIManager()->setIsAbilitySelectEnabled(true);
}

void AbilityManager::addAbility(int32 index)
{
	auto rolled_ability = p_impl->_rolled_ability_list[index];

	//PlayerStateを強化
	God::getInstance().getPlayer().getPtrPlayerStateManager()->enhancePlayerState(rolled_ability.getParameter());

	p_impl->_achieved_ability_list.push_back(rolled_ability);
	p_impl->_achieved_id_list.push_back(rolled_ability.getId());
}

std::vector<Ability>& AbilityManager::getRolledAbilityList() const
{
	return p_impl->_rolled_ability_list;
}
