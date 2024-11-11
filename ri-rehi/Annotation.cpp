#include "stdafx.h"
#include "Annotation.h"

#include "AssetKey.h"
#include "God.h"

struct Annotation::Impl
{
	void stage1() const
	{
		auto world = God::getInstance().getWorld();
		FontAsset(AssetKey::pixel_b30)(U"1.WASDで移動をします").draw(world.indexPos2worldPos({3, 11}, true), Palette::White);
		FontAsset(AssetKey::pixel_b30)(U"2.左クリックで射撃").draw(world.indexPos2worldPos({8, 11}, true), Palette::White);
		FontAsset(AssetKey::pixel_b30)(U"3.スライムを倒しましょう").draw(world.indexPos2worldPos({13, 11}, true), Palette::White);
		FontAsset(AssetKey::pixel_b30)(U"4.次のステージに行くには      が必要です").draw(world.indexPos2worldPos({19, 11}, true), Palette::White);
		TextureAsset(AssetKey::key).scaled(0.8).drawAt(Vec2{2900, 1485});
	}

	void stage2()
	{
		auto world = God::getInstance().getWorld();
		FontAsset(AssetKey::pixel_b30)(U"レベルアップすると能力を").draw(world.indexPos2worldPos({13, 7}, true), Palette::White);
		FontAsset(AssetKey::pixel_b30)(U"獲得することが出来ます").draw(world.indexPos2worldPos({13, 7}, true) + Vec2{0, 40}, Palette::White);
	}

	void stage3()
	{

	}
};

Annotation::Annotation() : p_impl(std::make_shared<Impl>())
{
}

void Annotation::init()
{
}

void Annotation::update(double delta_time)
{
}

void Annotation::draw() const
{
	switch (God::getInstance().getStageNum())
	{
	case 1:
		p_impl->stage1();
		break;
	case 2:
		p_impl->stage2();
		break;
	case 3:
		p_impl->stage3();
		break;
	}
}
