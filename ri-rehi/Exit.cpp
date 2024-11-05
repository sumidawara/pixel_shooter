#include "stdafx.h"
#include "Exit.h"

#include "AssetKey.h"
#include "God.h"
#include "GraphicSetting.h"

struct Exit::Impl
{
	RectF _rectf;
	int32 _enter_counter;
};

Exit::Exit() : p_impl(std::make_shared<Impl>())
{
}

void Exit::init(Vec2 pos)
{
	auto size = Vec2{GraphicSetting::getNormalTileWidth(), GraphicSetting::getNormalTileHeight()};
	p_impl->_rectf = RectF{pos, size};
	p_impl->_enter_counter = 0;
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
		//Transition開始
		if(p_impl->_enter_counter == 0)
		{
			p_impl->_enter_counter += 1;
			God::getInstance().getPtrGameSceneGUIManager()->setTransitionState(GameSceneTransitionType::Starting);
		}
	}
}

ICollidableType Exit::getType() const
{
	return T_Exit;
}
