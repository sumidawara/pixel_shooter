#pragma once
class MathEx
{
public:
	static Vec2 randomVec2(double length);
	static double distance(Vec2 pos1, Vec2 pos2);
	static std::vector<int> generateUniqueRandomNumbers(int32 min, int32 max, int32 count);
private:
};

