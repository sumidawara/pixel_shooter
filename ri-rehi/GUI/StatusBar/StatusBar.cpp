#include "stdafx.h"
#include "StatusBar.h"
#include "HPBlock.h"
#include "ExpBlock.h"
#include "God.h"
#include "DebugSetting.h"

struct StatusBar::Impl
{
	RectF _rectf;
	HPBlock _hpblock;
	ExpBlock _expblock;
};

StatusBar::StatusBar() : p_impl(std::make_shared<Impl>())
{

}

void StatusBar::init(Vec2 pos)
{
	auto size = Vec2{1920, (1080 - pos.y)};
	auto rectf = RectF{pos, size};
    p_impl->_rectf = rectf;

	auto hpblock_pos = pos + Vec2{50, 40};
	p_impl->_hpblock.init(hpblock_pos);

	auto expblock_pos = pos + Vec2{940, 40};
	p_impl->_expblock.init(expblock_pos);
}

void StatusBar::update(double delta_time)
{
	auto ptr_player_state_manager = God::getInstance().getPlayer().getPtrPlayerStateManager();
	auto player_state = ptr_player_state_manager->getPlayerState();

	p_impl->_hpblock.setHP(player_state.current_hp, player_state.max_hp);

	p_impl->_expblock.setLevel(player_state.level);
	p_impl->_expblock.setRemainingExpToNextLevelUp(ptr_player_state_manager->getRemainingExpToNextLevelUp());
}

void StatusBar::draw() const
{
	p_impl->_rectf.draw(Palette::Black);
	if(DebugSetting::getIsGuiDebuggingVisible()) p_impl->_rectf.draw(DebugSetting::getGuiDebugColor());

	p_impl->_hpblock.draw();

	p_impl->_expblock.draw();
}
