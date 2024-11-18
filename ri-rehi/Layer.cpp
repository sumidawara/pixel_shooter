#include "stdafx.h"
#include "Layer.h"
#include "GraphicSetting.h"
#include "AssetManager.h"
#include "God.h"
#include "TileIndexKey.h"

struct Layer::Impl
{
	std::shared_ptr<Grid<int32>> _index_grid;
	std::shared_ptr<Grid<std::shared_ptr<Block>>> _block_grid;

	Vec2 _world_pos;
	Point _world_size;

	LayerType _layer_type;

	void initGrids(const LayerJsonData& layer_json_data)
	{
		auto world_size = layer_json_data.world_size;
		_world_pos = layer_json_data.world_pos;
		_world_size = world_size;

		_index_grid = std::make_shared<Grid<int32>>(world_size.x, world_size.y, -1);
		_block_grid = std::make_shared<Grid<std::shared_ptr<Block>>>(world_size.x, world_size.y);

		for (int32 gy = 0; gy < world_size.y; gy++)
		{
			for (int32 gx = 0; gx < world_size.x; gx++)
			{
				int32 index = layer_json_data.index_data[gx + gy * layer_json_data.world_size.x];

				//_index_gridの初期化
				_index_grid->at(gy, gx) = index;

				AssetName asset_name = AssetManager::tilemapX_Y(index);
				RectF rectf{
					layer_json_data.world_pos.x + GraphicSetting::getNormalTileWidth() * gx,
					layer_json_data.world_pos.y + GraphicSetting::getNormalTileHeight() * gy,
					GraphicSetting::getNormalTileWidth(),
					GraphicSetting::getNormalTileHeight()
				};
				bool is_collidable;
				if (_layer_type == L_TerrainObject)
				{
					is_collidable = true;
				}
				else
				{
					is_collidable = false;
				}

				Block block{};
				block.init(rectf, asset_name, index, is_collidable);
				auto ptr_block = std::make_shared<Block>(block);

				//_block_gridの初期化
				_block_grid->at(gy, gx) = ptr_block;
			}
		}
	}

	//L_EntityPlacementだけが呼び出し
	void placeEntity()
	{
		auto enemy_manager = God::getInstance().getEnemyManager();

		for (int32 gy = 0; gy < _world_size.y; gy++)
		{
			for (int32 gx = 0; gx < _world_size.x; gx++)
			{
				switch (_index_grid->at(gy, gx))
				{
				case TileIndexKey::player:
					auto initial_player_pos = indexPos2worldPos(Point{gx, gy}, true);
					God::getInstance().setInitialPlayerPos(initial_player_pos);
					break;

				case TileIndexKey::exit:
					auto exit_pos = indexPos2worldPos(Point{gx, gy}, false);
					God::getInstance().setExitPos(exit_pos);
					break;

				case TileIndexKey::slime:
					enemy_manager->createEnemy(EnemyType::Slime, indexPos2worldPos(Point{gx, gy}, true));
					break;
				case TileIndexKey::white_eye:
					enemy_manager->createEnemy(EnemyType::WhiteEye, indexPos2worldPos(Point{gx, gy}, false));
					break;
				case TileIndexKey::ghost:
					enemy_manager->createEnemy(EnemyType::Ghost, indexPos2worldPos(Point{gx, gy}, false));
					break;
				case TileIndexKey::skelton:
					enemy_manager->createEnemy(EnemyType::Skelton, indexPos2worldPos(Point{gx, gy}, false));
					break;
				}
			}
		}

		//敵の中の1体だけに鍵を渡す
		enemy_manager->giveKeyToOneEnemy();
	}

	Vec2 indexPos2worldPos(Point index_pos, bool is_center)
	{
		auto NORMAL_WIDTH = GraphicSetting::getNormalTileWidth();
		auto NORMAL_HEIGHT = GraphicSetting::getNormalTileHeight();
		Vec2 worldpos = {_world_pos.x + index_pos.x * NORMAL_WIDTH, _world_pos.y + index_pos.y * NORMAL_HEIGHT};

		if (is_center)
		{
			worldpos += Vec2{NORMAL_WIDTH / 2, NORMAL_HEIGHT / 2};
		}

		return worldpos;
	}
};

Layer::Layer() : p_impl(std::make_shared<Impl>())
{
}

void Layer::init(const LayerJsonData& layer_json_data, LayerType layer_type)
{
	p_impl->_layer_type = layer_type;
	switch (layer_type)
	{
	case L_Ground:
		p_impl->initGrids(layer_json_data);
		break;
	case L_TerrainObject:
		p_impl->initGrids(layer_json_data);
		break;
	case L_EntityPlacement:
		p_impl->initGrids(layer_json_data);
		p_impl->placeEntity();
		break;
	}
}

void Layer::update()
{
}

void Layer::draw() const
{
	for (int32 gy = 0; gy < p_impl->_world_size.y; gy++)
	{
		for (int32 gx = 0; gx < p_impl->_world_size.x; gx++)
		{
			p_impl->_block_grid->at(gy, gx)->draw();
		}
	}
}

std::shared_ptr<Grid<int32>> Layer::getIndexGrid()
{
	return p_impl->_index_grid;
}

std::shared_ptr<Grid<std::shared_ptr<Block>>> Layer::getBlockGrid()
{
	return p_impl->_block_grid;
}
