#include "stdafx.h"
#include "DebugSetting.h"

bool DebugSetting::_is_collision_rect_visible = false;
bool DebugSetting::_is_view_range_visible = false;
bool DebugSetting::_is_particle_rect_visible = false;
bool DebugSetting::_is_gui_debugging_visible = false;
bool DebugSetting::_is_entity_placement_layer_visible = false;

ColorF DebugSetting::_collision_color = ColorF{ 1.0, 0.0, 0.0, 0.3 };
ColorF DebugSetting::_view_range_color = ColorF{ 0.0, 1.0, 0.0, 0.3 };
ColorF DebugSetting::_gui_debug_color = ColorF{ 1.0, 0.0, 0.0, 0.3 };
ColorF DebugSetting::_particle_color = ColorF{ 1.0, 0.0, 0.0, 0.3 };


bool DebugSetting::getIsCollisionRectVisible()
{
    return _is_collision_rect_visible;
}
void DebugSetting::setIsCollisionRectVisible(bool value)
{
	_is_collision_rect_visible = value;
}

bool DebugSetting::getIsViewRangeVisible()
{
	return _is_view_range_visible;
}
void DebugSetting::setIsViewRangeVisible(bool value)
{
	_is_view_range_visible = value;
}

bool DebugSetting::getIsParticleRectVisible()
{
	return _is_particle_rect_visible;
}
void DebugSetting::setIsParticleRectVisible(bool value)
{
	_is_particle_rect_visible = value;
}


bool DebugSetting::getIsGuiDebuggingVisible()
{
	return _is_gui_debugging_visible;
}
void DebugSetting::setIsGuiDebuggingVisible(bool value)
{
	_is_gui_debugging_visible = value;
}

bool DebugSetting::getIsEntityPlacementLayerVisible()
{
	return _is_entity_placement_layer_visible;
}
void DebugSetting::setIsEntityPlacementLayerVisible(bool value)
{
	_is_entity_placement_layer_visible = value;
}


ColorF DebugSetting::getCollisionColor()
{
	return _collision_color;
}

ColorF DebugSetting::getViewRangeColor()
{
	return _view_range_color;
}

ColorF DebugSetting::getGuiDebugColor()
{
	return _gui_debug_color;
}

ColorF DebugSetting::getParticleColor()
{
	return _particle_color;
}
