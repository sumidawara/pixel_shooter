#include "stdafx.h"
#include "Exit.h"

#include "AssetKey.h"
#include "God.h"
#include "GraphicSetting.h"

struct Exit::Impl
{
	RectF _rectf;
};

Exit::Exit() : p_impl(std::make_shared<Impl>())
{
}

void Exit::init(Vec2 pos)
{
	auto size = Vec2{GraphicSetting::getNormalTileWidth(), GraphicSetting::getNormalTileHeight()};
	p_impl->_rectf = RectF{pos, size};
}

void Exit::update(double delta_time)
{
}

void Exit::draw() const
{
	TextureAsset(AssetKey::exit).draw(p_impl->_rectf.pos);
}

RectF Exit::getBoundingShape() const
{
	return p_impl->_rectf;
}

void Exit::onCollision(const ICollidable& other)
{
	if(other.getType() == T_Player)
	{
		God::getInstance().setSceneTransitionData(Sc_Game);

	}
}

ICollidableType Exit::getType() const
{
	return T_Exit;
}
