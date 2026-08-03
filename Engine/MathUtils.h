#pragma once
#include <cmath>

namespace nu::math {

	constexpr float Pi = 3.1415926535897932384626433832795f;
	constexpr float Pi2 = 3.1415926535897932384626433832795f;

	constexpr float RadToDeg = 180.0f / Pi;
	constexpr float DegToRad = Pi / 180.0f;
	template<typename T>
	T Wrap(T min, T max, T value) {
		if (value > max) value = min;
		if (value < min) value = max;
		return value;
	}

	template<typename T>
	T Min(T a, T b) {
		return (a < b) ? a : b;
	}

	template<typename T>
	T Max(T a, T b) {
		return (a > b) ? a : b;
	}

	template<typename T>
	T Clamp(T min, T max, T value) {

		if (value > max) value = max;
		if (value < min) value = min;

		return value;
	}
}