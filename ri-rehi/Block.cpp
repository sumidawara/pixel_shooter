#include "stdafx.h"
#include "Block.h"

#include <complex.h>

#include "AssetManager.h"
#include "GraphicSetting.h"
#include "DebugSetting.h"

struct Block::Impl
{
	RectF _rectf;
	AssetName _tile_asset_name;
	int32 _id;
	bool _is_collidable;
};

Block::Block() : p_impl(std::make_shared<Impl>())
{
}

void Block::init(const RectF& rectf, const AssetName& tile_asset_name, int32 id, bool is_collidable)
{
	p_impl->_rectf = rectf;
	p_impl->_tile_asset_name = tile_asset_name;
	p_impl->_id = id;
	p_impl->_is_collidable = is_collidable;
}

void Block::update()
{
}

void Block::draw() const
{
	if (p_impl->_id != -1)
	{
		RectF clippedRect{
			GraphicSetting::getExtendedLength(),
			GraphicSetting::getExtendedLength(),
			GraphicSetting::getNormalTileWidth(),
			GraphicSetting::getNormalTileHeight() };
		auto rect = TextureAsset(p_impl->_tile_asset_name)(clippedRect).draw(p_impl->_rectf.pos);

		if(p_impl->_is_collidable && DebugSetting::getIsCollisionRectVisible())
		{
			rect.draw(DebugSetting::getCollisionColor());
		}
	}
}

void Block::onCollision(const ICollidable& other)
{

}

std::variant<RectF, Circle> Block::getBoundingShape() const
{
	return p_impl->_rectf;
}

ICollidableType Block::getType() const
{
	return T_Block;
}

int32 Block::getId() const
{
	return p_impl->_id;
}
