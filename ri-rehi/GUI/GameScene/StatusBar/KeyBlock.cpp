#include "stdafx.h"
#include "KeyBlock.h"

#include "AssetKey.h"
#include "DebugSetting.h"
#include "God.h"
#include "GraphicSetting.h"

struct KeyBlock::Impl
{
	Vec2 _pos;
	Vec2 _key_pos;
	Vec2 _text_pos;
};

KeyBlock::KeyBlock() : p_impl(std::make_shared<Impl>())
{
}

void KeyBlock::init(Vec2 pos)
{
	p_impl->_pos = pos;
	p_impl->_key_pos = pos + Vec2{-5, -8};
	p_impl->_text_pos = pos + Vec2{100, 30};
}

void KeyBlock::update(double delta_time)
{
}

void KeyBlock::draw() const
{
	auto exit = God::getInstance().getPtrExit();

	auto rect = RectF{p_impl->_pos, Vec2{250, 100}};
	double thickness = 5;
	auto yellow = GraphicSetting::getYELLOW();

	//未取得
	if(exit->getIsLocked())
	{
		rect.draw(Palette::Black).drawFrame(thickness, Palette::White);

		{
			const ScopedCustomShader2D shader{PixelShaderAsset{AssetKey::ps_grayscale}};
			auto rect_key = TextureAsset(AssetKey::key).scaled(0.8).draw(p_impl->_key_pos);
		}
		auto rect_text = FontAsset(AssetKey::pixel_b30)(U"未取得").draw(p_impl->_text_pos);
	}
	//取得済み
	else
	{
		rect.draw(Palette::Black).drawFrame(thickness, yellow);

		auto rect_key = TextureAsset(AssetKey::key).scaled(0.8).draw(p_impl->_key_pos);
		auto rect_text = FontAsset(AssetKey::pixel_b30)(U"取得済み").draw(p_impl->_text_pos, yellow);
	}

	if(DebugSetting::getIsGuiDebuggingVisible())
	{
		// rect.draw(DebugSetting::getGuiDebugColor());
		// rect_key.draw(DebugSetting::getGuiDebugColor());
		// rect_text.draw(DebugSetting::getGuiDebugColor());
	}
}
