#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"

namespace nc
{
	struct Particle
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		Color color;
		float lifetime;
		bool active{ false };
	};
}