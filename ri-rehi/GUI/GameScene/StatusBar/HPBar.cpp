#include "stdafx.h"
#include "HPBar.h"

#include "AssetKey.h"
#include "God.h"

struct HPBar::Impl
{
	RectF _rectf;
	RectF _rectf_hp;

	double _hp_ratio;

	double _padding = 15;
	double _border_width = 5;

	ColorF _rectf_color{ 0.0, 0.0, 0.0, 1.0 };
	ColorF _rectf_hp_color = GraphicSetting::getPINK();
	ColorF _rectf_hp_border_color = Palette::White;

	Vec2 text_center_pos;
};

HPBar::HPBar() : p_impl(std::make_shared<Impl>())
{

}


void HPBar::init(const RectF& rectf)
{
	auto state = God::getInstance().getPlayer().getPlayerState();
	p_impl->_rectf = rectf;
	p_impl->_hp_ratio = static_cast<double>(state.current_hp) /static_cast<double>(state.max_hp);
	p_impl->text_center_pos = rectf.center();

	Vec2 rectf_hp_pos = p_impl->_rectf.pos + Vec2(p_impl->_padding, p_impl->_padding);
	Vec2 rectf_max_hp_size = p_impl->_rectf.size - Vec2(p_impl->_padding, p_impl->_padding) * 2;
	Vec2 rectf_hp_size = { rectf_max_hp_size.x * p_impl->_hp_ratio, rectf_max_hp_size.y};
	p_impl->_rectf_hp = {rectf_hp_pos, rectf_hp_size};
}

void HPBar::update(double delta_time)
{
	//hp_ratioの計算
	auto state = God::getInstance().getPlayer().getPlayerState();
	p_impl->_hp_ratio = static_cast<double>(state.current_hp) /static_cast<double>(state.max_hp);

	//rectf_hpの設定
	Vec2 rectf_hp_pos = p_impl->_rectf.pos + Vec2(p_impl->_padding, p_impl->_padding);
	Vec2 rectf_max_hp_size = p_impl->_rectf.size - Vec2(p_impl->_padding, p_impl->_padding) * 2;
	Vec2 rectf_hp_size = { rectf_max_hp_size.x * p_impl->_hp_ratio, rectf_max_hp_size.y};
	p_impl->_rectf_hp = {rectf_hp_pos, rectf_hp_size};
}

void HPBar::draw() const
{
	//バーの描画
	p_impl->_rectf.draw(p_impl->_rectf_color);
	p_impl->_rectf.drawFrame(p_impl->_border_width, p_impl->_rectf_hp_border_color);
	p_impl->_rectf_hp.draw(p_impl->_rectf_hp_color);

	//数値の描画
	auto state = God::getInstance().getPlayer().getPlayerState();
	String text = Format(state.current_hp) + U"/" + Format(state.max_hp);
	FontAsset(AssetKey::pixel_b48)(text).drawAt(p_impl->text_center_pos);
}

Vec2 HPBar::getPos() const
{
	return p_impl->_rectf.pos;
}
