#include "stdafx.h"
#include "GridUtil.h"

bool GridUtil::isGridIndexValid(Point index_pos, Point world_size)
{
	if (0 <= index_pos.x && index_pos.x < world_size.x &&
	0 <= index_pos.y && index_pos.y < world_size.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
