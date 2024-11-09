#include "stdafx.h"
#include "GridChaseBehavior.h"

#include "God.h"
#include "GridUtil.h"
#include "MathEx.h"

struct GridChaseBehavior::AdjacentBlock
{
	Point direction;
	int32 distance = -2;

	AdjacentBlock(Point _direction)
	{
		direction = _direction;
	}
};

void GridChaseBehavior::execute(MobAIContext& mob_ai_context, double delta_time)
{


	auto world = God::getInstance().getWorld();
	auto distance_field = world.getDistanceField();

	auto enemy_center_pos = mob_ai_context.enemy_rectf.center();
	auto index_pos = world.worldPos2indexPos(enemy_center_pos);
	auto block_center_pos = world.indexPos2worldPos(index_pos, true);

	std::vector<AdjacentBlock> adjacent_blocks = {
		AdjacentBlock({0, 0}),
		AdjacentBlock({0, 1}),
		AdjacentBlock({1, 0}),
		AdjacentBlock({0, -1}),
		AdjacentBlock({-1, 0})
	};

	//距離を求める
	for (auto& adjacent_block : adjacent_blocks)
	{
		if(not GridUtil::isGridIndexValid(index_pos + adjacent_block.direction, world.getSize()))
		{
			return;
		}

		adjacent_block.distance = distance_field->at(index_pos + adjacent_block.direction);
		if(adjacent_block.distance == -1) adjacent_block.distance = 9999;
	}

	//距離の小さいものを選ぶ
	auto min_it = std::min_element(adjacent_blocks.begin(), adjacent_blocks.end(),
		[](const AdjacentBlock& a, const AdjacentBlock& b)
		{
			return a.distance < b.distance;
		});

	if(min_it->direction != previous_dir)
	{
		//早すぎると過ぎてしまう
		if(MathEx::distance(enemy_center_pos, block_center_pos) > 20)
		{
			auto move_amount = mob_ai_context.direction.normalize() * mob_ai_context.run_speed * delta_time;
			mob_ai_context.enemy_rectf.moveBy(move_amount);

			return;
		}
	}

	mob_ai_context.direction = min_it->direction;
	previous_dir = min_it->direction;

	auto move_amount = mob_ai_context.direction.normalize() * mob_ai_context.run_speed * delta_time;
	mob_ai_context.enemy_rectf.moveBy(move_amount);

}
