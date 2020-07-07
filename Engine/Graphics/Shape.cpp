#include "pch.h"
#include "Shape.h"
#include <fstream>

namespace nc
{
	bool Shape::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

				//Read color
				//Read points
			while (!stream.eof())
			{
				Vector2 point;
				stream >> point;

				m_points.push_back(point);
			}
				
			stream.close();
		}
		return success;
	}
	void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
	{
		graphics.SetColor(m_color);

		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			nc::Vector2 p1 = m_points[i];
			nc::Vector2 p2 = m_points[i++];
		}
	}
}