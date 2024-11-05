#include "stdafx.h"
#include "HPBar.h"

#include "God.h"

struct HPBar::Impl
{
	RectF _rectf;

	int32 _max_hp;
	int32 _current_hp;
	double _hp_ratio;

	double _padding = 15;
	double _border_width = 5;

	ColorF _rectf_color{ 0.0, 0.0, 0.0, 1.0 };
	ColorF _rectf_hp_color = GraphicSetting::getPINK();
	ColorF _rectf_hp_border_color = Palette::White;

};

HPBar::HPBar() : p_impl(std::make_shared<Impl>())
{

}


void HPBar::init(RectF rectf, int32 current_hp, int32 max_hp)
{
	p_impl->_rectf = rectf;
	p_impl->_current_hp = current_hp,
	p_impl->_max_hp = max_hp,
	p_impl->_hp_ratio = static_cast<double>(current_hp) /static_cast<double>(max_hp);
}

void HPBar::update(double delta_time)
{
}

void HPBar::draw() const
{
	Vec2 rectf_hp_pos = p_impl->_rectf.pos + Vec2(p_impl->_padding, p_impl->_padding);
	Vec2 rectf_max_hp_size = p_impl->_rectf.size - Vec2(p_impl->_padding, p_impl->_padding) * 2;
	Vec2 rectf_hp_size = { rectf_max_hp_size.x * p_impl->_hp_ratio, rectf_max_hp_size.y};
	RectF rectf_hp{ rectf_hp_pos, rectf_hp_size};

	p_impl->_rectf.draw(p_impl->_rectf_color);
	p_impl->_rectf.drawFrame(p_impl->_border_width, p_impl->_rectf_hp_border_color);
	rectf_hp.draw(p_impl->_rectf_hp_color);
}

Vec2 HPBar::getPos() const
{
	return p_impl->_rectf.pos;
}

void HPBar::setHP(int32 current_hp, int32 max_hp)
{
	p_impl->_current_hp = current_hp;
	p_impl->_max_hp = max_hp;
	p_impl->_hp_ratio = static_cast<double>(p_impl->_current_hp) / static_cast<double>(p_impl->_max_hp);
}
