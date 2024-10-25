#include "stdafx.h"
#include "CursorEx.h"

#include "Debug.h"
#include "DebugSetting.h"
#include "MathEx.h"

struct CursorEx::Impl
{
	Texture _cursor_tex{ U"resources/img/cursor.png" };

	Vec2 _start_point;
	Vec2 _end_point;
	double _distance;
	double _ruler_thickness = 3;


	int32 _writeline_index = 3;

	void updateRuler()
	{
		if(MouseR.down())
		{
			_start_point = Cursor::Pos();
		}

		if(MouseR.pressed())
		{
			_end_point = Cursor::Pos();
			_distance = MathEx::distance(_start_point, _end_point);
		}
	}

	void writeline()
	{
		if(Debug::getInstance().getDebugScreenIndex() == _writeline_index)
		{
			Debug::getInstance().writeline(_writeline_index, U"CursorPos : " + Format(Cursor::Pos()));
			if(MouseR.pressed())
			{
				Debug::getInstance().writeline(_writeline_index, U"StartPos : " + Format(_start_point));
				Debug::getInstance().writeline(_writeline_index, U"EndPos   : " + Format(_end_point));
				Debug::getInstance().writeline(_writeline_index, U"Distance : " + Format(_distance));
			}
		}
	}
};

CursorEx::CursorEx() : p_impl(std::make_shared<Impl>())
{
}

void CursorEx::init()
{
}

void CursorEx::update(double delta_time)
{
	Cursor::RequestStyle(CursorStyle::Hidden);
	p_impl->updateRuler();
	p_impl->writeline();
}

void CursorEx::draw() const
{
	auto is_gui_debugging_visible = DebugSetting::getIsGuiDebuggingVisible();
	{
		ScopedRenderStates2D blend(BlendState{ true, Blend::InvDestColor });

		if(is_gui_debugging_visible)
		{
			if(MouseR.pressed())
			{

			}
			else
			{
				Circle(Cursor::PosF(), 3).draw(Palette::White);
			}
		}
		else
		{
			p_impl->_cursor_tex.scaled(2).drawAt(Cursor::PosF());
		}
	}

	if(is_gui_debugging_visible)
	{
		if(MouseR.pressed())
		{
			auto start = p_impl->_start_point;
			auto end = p_impl->_end_point;
			Line(start, end).draw(p_impl->_ruler_thickness, Palette::White);
		}
	}
}
