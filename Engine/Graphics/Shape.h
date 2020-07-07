#pragma once
#include "core.h"
#include <vector>
#include <string>
#include "..\Math\Color.h"

namespace nc
{
	class Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<nc::Vector2>& points, const Color& color) : m_points{ points }, m_color { color }

		bool Load(std::string& fileame);

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1.0f, float angle = 0.0f);

		void SetColor(Color color) { m_color = color; }

		void Draw(Core::Graphics& graphics);
	};
}

/*
//USED FOR SHAPE CLASS
	for (size_t i = 0; i < points.size()- 1; i++)
	{
		//local space points
		nc::Vector2 p1 = points[i] * 4.0f;
		nc::Vector2 p2 = points[i + 1] * 4.0f;

		//Transform
		//Scale
		p1 = p1 * scale;
		p2 = p2 * scale;
		//rotate
		p1 = nc::Vector2::Rotate(p1, angle);
		p2 = nc::Vector2::Rotate(p2, angle);
		//Translate
		p1 = p1 + position;
		p2 = p2 + position;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
*/