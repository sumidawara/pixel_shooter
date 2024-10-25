#include "stdafx.h"
#include "Layer.h"
#include "GraphicSetting.h"
#include "AssetManager.h"
#include "God.h"

struct Layer::Impl
{
	std::vector<int32> _index_data; //インデックスをつけたい
	std::vector<std::shared_ptr<Block>> _block_list; //インデックスをつけたい

};

Layer::Layer() : p_impl(std::make_shared<Impl>())
{

}

void Layer::init(LayerJsonData layer_json_data)
{
	for (int32 gy = 0; gy < layer_json_data.world_size.y; gy++)
	{
		for (int32 gx = 0; gx < layer_json_data.world_size.x; gx++)
		{
			int32 tile_index = layer_json_data.index_data[gx + gy * layer_json_data.world_size.x];
			AssetName asset_name = AssetManager::tilemapX_Y(tile_index);
			RectF rectf{
				layer_json_data.world_size.x + GraphicSetting::getNormalTileWidth() * gx,
				layer_json_data.world_size.y + GraphicSetting::getNormalTileHeight() * gy,
				GraphicSetting::getNormalTileWidth(),
				GraphicSetting::getNormalTileHeight() };

			Block block{};
			block.init(rectf, asset_name, tile_index);
			auto ptr_block = std::make_shared<Block>(block);

			p_impl->_block_list.push_back(ptr_block);
		}
	}
}

void Layer::update()
{
}

void Layer::draw() const
{
	Point world_size = God::getInstance().getWorld().getSize();

	for (int32 gy = 0; gy < world_size.y; gy++)
	{
		for (int32 gx = 0; gx < world_size.x; gx++)
		{
			p_impl->_block_list[gx + gy * world_size.x]->draw();
		}
	}
}

std::vector<std::shared_ptr<Block>>& Layer::getBlockPtrList()
{
	return p_impl->_block_list;
}
