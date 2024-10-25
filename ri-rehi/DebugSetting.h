#pragma once
class DebugSetting
{
public:
	static bool getIsCollisionRectVisible();
	static void setIsCollisionRectVisible(bool value);

	static bool getIsViewRangeVisible();
	static void setIsViewRangeVisible(bool value);

	static bool getIsParticleRectVisible();
	static void setIsParticleRectVisible(bool value);

	static bool getIsGuiDebuggingVisible();
	static void setIsGuiDebuggingVisible(bool value);


	static ColorF getCollisionColor();
	static ColorF getViewRangeColor();
	static ColorF getGuiDebugColor();
	static ColorF getParticleColor();

private:
	static bool _is_collision_rect_visible;
	static bool _is_view_range_visible;
	static bool _is_particle_rect_visible;
	static bool _is_gui_debugging_visible;


	static ColorF _collision_color;
	static ColorF _view_range_color;
	static ColorF _gui_debug_color;
	static ColorF _particle_color;
};

