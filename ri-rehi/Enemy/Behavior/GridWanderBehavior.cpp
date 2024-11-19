#include "stdafx.h"
#include "GridWanderBehavior.h"

#include "God.h"
#include "GridUtil.h"
#include "MathEx.h"

struct GridWanderBehavior::AdjacentBlock
{
	Point direction;
	int32 distance = -2;

	AdjacentBlock(Point _direction)
	{
		direction = _direction;
	}
};

void GridWanderBehavior::execute(MobAIContext& mob_ai_context, double delta_time)
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

	std::vector<AdjacentBlock> appropriate_adjacent_blocks;

	//距離を求める
	for (auto& adjacent_block : adjacent_blocks)
	{
		if(not GridUtil::isGridIndexValid(index_pos + adjacent_block.direction, world.getSize()))
		{
			return;
		}

		adjacent_block.distance = distance_field->at(index_pos + adjacent_block.direction);
		if(adjacent_block.distance != -1)
		{
			appropriate_adjacent_blocks.push_back(adjacent_block);
		}
	}

	//適当に選ぶ
	int32 random_index = Random(0, static_cast<int32>(appropriate_adjacent_blocks.size() - 1));
	auto planned_direction = appropriate_adjacent_blocks[random_index];

	if(planned_direction.direction != previous_dir)
	{
		//早すぎると過ぎてしまう
		if(MathEx::distance(enemy_center_pos, block_center_pos) > 20)
		{
			auto move_amount = mob_ai_context.direction.normalize() * mob_ai_context.run_speed * delta_time;
			mob_ai_context.enemy_rectf.moveBy(move_amount);

			return;
		}
	}

	mob_ai_context.direction = planned_direction.direction;
	previous_dir = planned_direction.direction;

	auto move_amount = mob_ai_context.direction.normalize() * mob_ai_context.run_speed * delta_time;
	mob_ai_context.enemy_rectf.moveBy(move_amount);

}
