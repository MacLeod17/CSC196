#pragma once

#include <random>

namespace gk
{
	float random()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0/10 = 0, 5/10 = .5
	}

	float random(float min, float max)
	{
		if (min > max)
		{
			std::swap(min, max);
		}
		return min + (max - min) * random();
	}
}