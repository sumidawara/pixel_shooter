#include "stdafx.h"
#include "World.h"
#include "LayerJsonData.h"

struct World::Impl
{
	Point _world_size;
	Vec2 _world_pos;

	std::shared_ptr<Layer> _ptr_terrain_object_layer;
	std::shared_ptr<Layer> _ptr_ground_layer;

	void loadWorldJSON(String file_path)
	{
		const JSON json = JSON::Load(file_path);
		if (not json) throw Error{ U"Failed to load " + file_path };

		Point world_size = {json[U"width"].get<int32>(), json[U"height"].get<int32>()};
		_world_size.x = world_size.x;
		_world_size.y = world_size.y;

		Array<LayerJsonData> layer_json_data_list;
		for (const auto& layer : json[U"layers"].arrayView())
		{
			LayerJsonData layer_json_data;
			layer_json_data.world_size = world_size;
			for (const auto& n : layer[U"data"].arrayView())
			{
				//空白タイルのidは-1（Tiledの標準は0）
				layer_json_data.index_data.push_back(n.get<int32>() - 1);
			}

			layer_json_data_list << layer_json_data;
		}

		//layer_json_data_listから諸々のレイヤーの初期化
		_ptr_ground_layer = std::make_shared<Layer>();
		_ptr_terrain_object_layer = std::make_shared<Layer>();

		_ptr_ground_layer->init(layer_json_data_list[0]);
		_ptr_terrain_object_layer->init(layer_json_data_list[1]);
	}
};

World::World() : p_impl(std::make_shared<Impl>())
{
}

void World::init(Vec2 pos, String file_path)
{
	p_impl->_world_pos = pos;
	p_impl->loadWorldJSON(file_path);
}

void World::update(double delta_time)
{
	p_impl->_ptr_ground_layer->update();
	p_impl->_ptr_terrain_object_layer->update();
}

void World::draw() const
{
	p_impl->_ptr_ground_layer->draw();
	p_impl->_ptr_terrain_object_layer->draw();
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
