#include "stdafx.h"
#include "MathEx.h"

Vec2 MathEx::randomVec2(double length)
{
	Vec2 normalized_rand_vec = Vec2{ Random(-1.0, 1.0) , Random(-1.0, 1.0) }.normalized();

    return normalized_rand_vec * length;
}

double MathEx::distance(Vec2 pos1, Vec2 pos2)
{
	return sqrt(Pow((pos1.x - pos2.x), 2) + Pow((pos1.y - pos2.y), 2));
}

std::vector<int> MathEx::generateUniqueRandomNumbers(int32 min, int32 max, int32 count)
{
	// 整数の集合を使って重複を排除
	std::unordered_set<int> uniqueNumbers;

	// 重複なしの整数を生成
	while (uniqueNumbers.size() < count) {
		uniqueNumbers.insert(Random(min, max));
	}

	// std::vectorに変換して返す
	return std::vector<int>(uniqueNumbers.begin(), uniqueNumbers.end());
}

