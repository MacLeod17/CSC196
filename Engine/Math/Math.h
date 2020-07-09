#pragma once

#include "Vector2.h"

namespace gk
{
	const float PI = 3.14159265358979f;
	const float TWO_PI = PI * 2.0f;
	const float HALF_PI = PI * 0.5f;
	const float RAD_TO_DEG = (180.0f / PI);
	const float DEG_TO_RAD = (PI / 180.0f);

	inline float RadiansToDegrees(float radians)
	{
		return radians * (180.0f / PI);
	}

	inline float DegreesToRadians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	template <typename T>
	inline T Clamp(T v, T min, T max)
	{
		if (v < min) v = min;
		if (v > max) v = max;

		return v;
	}

	template <>
	inline gk::Vector2 Clamp<gk::Vector2>(gk::Vector2 v, gk::Vector2 min, gk::Vector2 max)
	{
		v.x = Clamp(v.x, min.x, max.x);
		v.y = Clamp(v.y, min.y, max.y);

		return v;
	}

	template <typename T>
	inline T Lerp(T a, T b, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return a + ((b - a) * t);
	}
}
