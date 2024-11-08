#pragma once
class MathEx
{
public:
	static Vec2 randomVec2(double length);
	static double distance(Vec2 pos1, Vec2 pos2);
	static Vec2 lerp(Vec2 start, Vec2 end, double t);

	static std::vector<int> generateUniqueRandomNumbers(int32 min, int32 max, int32 count);
	static int32 weightedRandomDraw(const std::vector<int32>& weight_list, const std::vector<int32>& id_list);
private:
};

