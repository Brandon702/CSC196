#pragma once
#include "Vector2.h"

namespace nc
{
	struct Transform
	{
		Vector2 position;
		float scale;
		float angle;

		Transform() : position{ 0,0 }, scale{ 0 }, angle{ 0 } {}
		Transform(const Vector2 position, float scale, float angle) : position{ position }, scale{ scale }, angle{ angle } {}
	
		friend std::istream& operator >> (std::istream& stream, Transform& transform);
	};
}