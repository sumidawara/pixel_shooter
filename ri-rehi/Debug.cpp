#include "stdafx.h"
#include "Debug.h"
#include "DebugSetting.h"

struct Debug::Impl
{
	//-1は何も表示しない
	int32 _debug_screen_index = -1;

	int32 _log_count = 10;
	std::vector<std::vector<String>> _log_list;

	Font _font;

	Impl() : _log_list(_log_count)
	{
	}

	void input()
	{
		if (Key0.down()) changePressedNumKey(0);
		if (Key1.down()) changePressedNumKey(1);
		if (Key2.down()) changePressedNumKey(2);
		if (Key3.down()) changePressedNumKey(3);
		if (Key4.down()) changePressedNumKey(4);
		if (Key5.down()) changePressedNumKey(5);
		if (Key6.down()) changePressedNumKey(6);
		if (Key7.down()) changePressedNumKey(7);
		if (Key8.down()) changePressedNumKey(8);
		if (Key9.down()) changePressedNumKey(9);
	}

	void changePressedNumKey(int key_num)
	{
		if (_debug_screen_index == key_num)
		{
			_debug_screen_index = -1;
			resetDebugSetting();
		}
		else
		{
			_debug_screen_index = key_num;
			resetDebugSetting();
			changeDebugSetting(key_num);
		}
	}

	void resetDebugSetting()
	{
		DebugSetting::setIsCollisionRectVisible(false);
		DebugSetting::setIsViewRangeVisible(false);
		DebugSetting::setIsGuiDebuggingVisible(false);
		DebugSetting::setIsParticleRectVisible(false);
		DebugSetting::setIsEntityPlacementLayerVisible(false);
	}

	void changeDebugSetting(int32 debug_screen_index)
	{
		switch (debug_screen_index)
		{
		case 1:
			//衝突判定描画
			DebugSetting::setIsCollisionRectVisible(true);
			//敵配置・プレイヤー配置・出口の配置の表示
			DebugSetting::setIsEntityPlacementLayerVisible(true);
			break;
		case 2:
			//敵キャラの視野
			DebugSetting::setIsViewRangeVisible(true);
			break;
		case 3:
			//GUIの位置に赤点あるいは赤の長方形
			DebugSetting::setIsGuiDebuggingVisible(true);
			break;
		case 4:
			//ParticleManagerでParticle数を表示
			DebugSetting::setIsParticleRectVisible(true);
			break;
		case 5:
			//アビリティーの表示


			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 0:
			break;
		}
	}
};

Debug::Debug() : p_impl(std::make_shared<Impl>())
{
}

Debug& Debug::getInstance()
{
	static Debug instance;
	return instance;
}

void Debug::init()
{
	auto path = FileSystem::GetFolderPath(SpecialFolder::SystemFonts) + U"msgothic.ttc";
	p_impl->_font = {20, path};
}

void Debug::update(double delta_time)
{
	p_impl->input();
}

void Debug::draw() const
{
	int32 debug_screen_index = p_impl->_debug_screen_index;
	if (debug_screen_index != -1)
	{
		auto print = detail::Print_impl{};
		print.setFont(p_impl->_font);

		print << U"DebugScreenIndex : " << debug_screen_index;
		print << U"-------------------------------";

		for (int32 line = 0; line < p_impl->_log_list[debug_screen_index].size(); line++)
		{
			print << p_impl->_log_list[debug_screen_index][line];
		}

		if(debug_screen_index !=0)
		{
			p_impl->_log_list[debug_screen_index].clear();
		}
	}
}

void Debug::writeline(int32 index, const String& content)
{
	p_impl->_log_list[index].push_back(content);
}

void Debug::writeline(int32 index)
{
	p_impl->_log_list[index].push_back(U"-------------------------------");
}

int32 Debug::getDebugScreenIndex()
{
	return p_impl->_debug_screen_index;
}
