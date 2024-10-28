#include "stdafx.h"
#include "World.h"

#include "DebugSetting.h"
#include "GraphicSetting.h"
#include "LayerJsonData.h"

struct World::Impl
{
	Point _world_size;
	Vec2 _world_pos;

	std::shared_ptr<Layer> _ptr_entity_placement_layer;
	std::shared_ptr<Layer> _ptr_terrain_object_layer;
	std::shared_ptr<Layer> _ptr_ground_layer;

	std::vector<LayerJsonData> loadWorldJSON(const StringView& file_path)
	{
		const JSON json = JSON::Load(file_path);
		if (not json) throw Error{ U"Failed to load " + file_path };

		Point world_size = {json[U"width"].get<int32>(), json[U"height"].get<int32>()};
		_world_size.x = world_size.x;
		_world_size.y = world_size.y;

		std::vector<LayerJsonData> layer_json_data_list;
		for (const auto& layer : json[U"layers"].arrayView())
		{
			LayerJsonData layer_json_data;
			layer_json_data.world_pos = _world_pos;
			layer_json_data.world_size = world_size;
			for (const auto& n : layer[U"data"].arrayView())
			{
				//空白タイルのidは-1（Tiledの標準は0）
				layer_json_data.index_data.push_back(n.get<int32>() - 1);
			}

			layer_json_data_list.push_back(layer_json_data);
		}

		return layer_json_data_list;
	}

	void initLayers(const std::vector<LayerJsonData>& layer_json_data_list)
	{
		_ptr_ground_layer = std::make_shared<Layer>();
		_ptr_terrain_object_layer = std::make_shared<Layer>();
		_ptr_entity_placement_layer = std::make_shared<Layer>();

		_ptr_ground_layer->init(layer_json_data_list[0], L_Ground);
		_ptr_terrain_object_layer->init(layer_json_data_list[1], L_TerrainObject);
		_ptr_entity_placement_layer->init(layer_json_data_list[2], L_EntityPlacement);
	}
};

World::World() : p_impl(std::make_shared<Impl>())
{
}

void World::init(Vec2 pos, const StringView& file_path)
{
	p_impl->_world_pos = pos;
	auto layer_json_data_list = p_impl->loadWorldJSON(file_path);
	p_impl->initLayers(layer_json_data_list);
}

void World::update(double delta_time)
{
	p_impl->_ptr_ground_layer->update();
	p_impl->_ptr_terrain_object_layer->update();
	p_impl->_ptr_entity_placement_layer->update();
}

void World::draw() const
{
	p_impl->_ptr_ground_layer->draw();
	p_impl->_ptr_terrain_object_layer->draw();

	if(DebugSetting::getIsEntityPlacementLayerVisible())
	{
		p_impl->_ptr_entity_placement_layer->draw();
	}
}

bool World::isBlockAtWorldPos(Vec2 worldPos)
{
	auto index_pos = worldPos2indexPos(worldPos);
	return isBlockAtIndexPos(index_pos);
}

bool World::isBlockAtIndexPos(Point index_pos)
{
	auto index_grid = p_impl->_ptr_terrain_object_layer->getIndexGrid();
	if(index_grid->at(index_pos.y, index_pos.x) != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Point World::worldPos2indexPos(Vec2 worldpos)
{
	auto base_pos = worldpos - p_impl->_world_pos;

	Point indexPos;
	indexPos.x = base_pos.x / GraphicSetting::getNormalTileWidth();
	indexPos.y = base_pos.y / GraphicSetting::getNormalTileHeight();

	return indexPos;
}

Vec2 World::getPos() const
{
	return p_impl->_world_pos;
}

Point World::getSize() const
{
	return p_impl->_world_size;
}


Layer World::getLayer(LayerType layer_type) const
{
	switch (layer_type)
	{
	case L_TerrainObject:
		return *p_impl->_ptr_terrain_object_layer;
	case L_Ground:
		return *p_impl->_ptr_ground_layer;
	default:
		throw Error(U"switch error");
	}

}

std::shared_ptr<Grid<std::shared_ptr<Block>>> World::getCollidableBlockGrid() const
{
	return p_impl->_ptr_terrain_object_layer->getBlockGrid();
}
