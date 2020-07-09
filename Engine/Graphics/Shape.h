#pragma once
#include "core.h"
#include <vector>
#include <string>
#include "..\Math\Color.h"
#include "..\Math\Vector2.h"
#include "..\Math\transform.h"

namespace nc
{
	class Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<nc::Vector2>& points, const Color& color) : m_points{ points }, m_color{ color }{};

		bool Load(const std::string& fileame);

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle);
		void Draw(Core::Graphics& graphics, const Transform& transform);

		void SetColor(Color color) { m_color = color; }
		const Color& GetColor() const { return m_color; }

	private:
		std::vector<nc::Vector2> m_points;
		Color m_color;
	};
}