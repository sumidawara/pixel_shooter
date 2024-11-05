#include "stdafx.h"
#include "World.h"

#include "Debug.h"
#include "DebugSetting.h"
#include "God.h"
#include "GraphicSetting.h"
#include "LayerJsonData.h"

struct World::Impl
{
	Point _world_size;
	Vec2 _world_pos;

	std::shared_ptr<Layer> _ptr_entity_placement_layer;
	std::shared_ptr<Layer> _ptr_terrain_object_layer;
	std::shared_ptr<Layer> _ptr_ground_layer;

	std::shared_ptr<Grid<int32>> _distance_field;

	std::vector<LayerJsonData> loadWorldJSON(const StringView& file_path)
	{
		const JSON json = JSON::Load(file_path);
		if (not json) throw Error{U"Failed to load " + file_path};

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

	Point worldPos2indexPos(Vec2 worldpos)
	{
		auto base_pos = worldpos - _world_pos;

		Point indexPos;
		indexPos.x = base_pos.x / GraphicSetting::getNormalTileWidth();
		indexPos.y = base_pos.y / GraphicSetting::getNormalTileHeight();

		return indexPos;
	}

	bool isGridIndexValid(Point p)
	{
		if (0 <= p.x && p.x < _world_size.x &&
			0 <= p.y && p.y < _world_size.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void calcDistanceField()
	{
		//distance_fieldを-2に初期化。-2は未訪問を表す。-1は障害物。
		_distance_field->fill(-2);

		auto playerIndexPos = worldPos2indexPos(God::getInstance().getPlayer().getCenterPos());
		std::queue<Point> q;
		q.push(Point{playerIndexPos.x, playerIndexPos.y});
		_distance_field->at(playerIndexPos.y, playerIndexPos.x) = 0;

		std::vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

		while (!q.empty())
		{
			Point p = q.front();
			q.pop();

			for (const auto& dir : directions)
			{
				Point np = p + dir;

				bool is_unvisited = _distance_field->at(np.y, np.x) == -2;
				if(isGridIndexValid(np) && is_unvisited)
				{
					auto block_grid = _ptr_terrain_object_layer->getBlockGrid();
					if(block_grid->at(np.y, np.x)->getId() == -1)
					{
						//空のマス(id = -1)のときは距離を計算
						_distance_field->at(np.y, np.x) = _distance_field->at(p.y, p.x) + 1;
						q.push(np);
					}
					else
					{
						//障害物がある場合は距離は-1
						_distance_field->at(np.y, np.x) = -1;
					}
				}
			}
		}

		for(int32 y = 0; y < _world_size.y ; y++)
		{
			for(int32 x = 0; x <_world_size.x; x++)
			{
				//未探索のところ(-2)は壁(-1)にしておく
				if(_distance_field->at(y, x) == -2)
				{
					_distance_field->at(y, x) = -1;
				}

			}
		}
	}

	void writelineDistanceField()
	{
		for(int32 y = 0; y < _world_size.y ; y++)
		{
			String line = U"";
			for(int32 x = 0; x <_world_size.x; x++)
			{
				//プレイヤーの場合は目立たせる
				if(_distance_field->at(y, x) == 0)
				{
					line += U"{: >4}"_fmt(U":P:");
				}
				else
				{
					line += U"{: >4}"_fmt(_distance_field->at(y, x));
				}
			}
			Debug::getInstance().writeline(8, line);
		}
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

	p_impl->_distance_field = std::make_shared<Grid<int32>>(p_impl->_world_size.x, p_impl->_world_size.y, -2);
}

void World::update(double delta_time)
{
	p_impl->_ptr_ground_layer->update();
	p_impl->_ptr_terrain_object_layer->update();
	p_impl->_ptr_entity_placement_layer->update();

	p_impl->calcDistanceField();
	p_impl->writelineDistanceField();
}

void World::draw() const
{
	p_impl->_ptr_ground_layer->draw();
	p_impl->_ptr_terrain_object_layer->draw();

	if (DebugSetting::getIsEntityPlacementLayerVisible())
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
	if (index_grid->at(index_pos.y, index_pos.x) != -1)
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
	return p_impl->worldPos2indexPos(worldpos);
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

std::shared_ptr<Grid<int32>> World::getDistanceField() const
{
	return p_impl->_distance_field;
}

std::shared_ptr<Grid<std::shared_ptr<Block>>> World::getCollidableBlockGrid() const
{
	return p_impl->_ptr_terrain_object_layer->getBlockGrid();
}
