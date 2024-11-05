#include "stdafx.h"
#include "Exit.h"

#include "AssetKey.h"
#include "God.h"
#include "GraphicSetting.h"

struct Exit::Impl
{
	RectF _rectf;
	int32 _enter_counter;

	bool _is_locked;
};

Exit::Exit() : p_impl(std::make_shared<Impl>())
{
}

void Exit::init(Vec2 pos)
{
	auto size = Vec2{GraphicSetting::getNormalTileWidth(), GraphicSetting::getNormalTileHeight()};
	p_impl->_rectf = RectF{pos, size};
	p_impl->_enter_counter = 0;
	p_impl->_is_locked = true;
}

void Exit::update(double delta_time)
{
}

void Exit::draw() const
{
	if(p_impl->_is_locked)
	{
		TextureAsset(AssetKey::locked_exit).draw(p_impl->_rectf.pos);
	}
	else
	{
		TextureAsset(AssetKey::exit).draw(p_impl->_rectf.pos);
	}
}

RectF Exit::getBoundingShape() const
{
	return p_impl->_rectf;
}

void Exit::onCollision(const ICollidable& other)
{
	if(other.getType() == T_Player)
	{
		if(not p_impl->_is_locked)
		{
			//Transition開始
			if(p_impl->_enter_counter == 0)
			{
				p_impl->_enter_counter += 1;
				God::getInstance().getPtrGameSceneGUIManager()->setTransitionState(GameSceneTransitionType::Starting);
			}
		}
	}
}

ICollidableType Exit::getType() const
{
	return T_Exit;
}

bool Exit::getIsLocked() const
{
	return p_impl->_is_locked;
}

void Exit::setIsLocked(bool value)
{
	p_impl->_is_locked = value;
}
