#include "stdafx.h"
#include "MathEx.h"

Vec2 MathEx::randomVec2(double length)
{
	Vec2 normalized_rand_vec = Vec2{Random(-1.0, 1.0), Random(-1.0, 1.0)}.normalized();

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
	while (uniqueNumbers.size() < count)
	{
		uniqueNumbers.insert(Random(min, max));
	}

	// std::vectorに変換して返す
	return std::vector<int>(uniqueNumbers.begin(), uniqueNumbers.end());
}

int32 MathEx::weightedRandomDraw(const std::vector<int32>& weight_list, const std::vector<int32>& id_list)
{
	int32 total_weight = 0;
	for (auto weight : weight_list)
	{
		total_weight += weight;
	}

	int random_weight = Random(0, total_weight - 1);

	int accumulated_weight = 0;
	for (int i = 0; i < weight_list.size(); i++)
	{
		accumulated_weight += weight_list[i];
		if (random_weight < accumulated_weight)
		{
			return id_list[i];
		}
	}

	return -1;
}
