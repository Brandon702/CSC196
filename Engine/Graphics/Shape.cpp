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
			stream >> m_color;

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
	void Shape::Draw(Core::Graphics& graphics, Vector2 position, float scale = 1.0f, float angle = 0.0f) 
        {
            graphics.SetColor(m_color.Pack888());
            for (size_t i = 0; i < m_points.size() - 1; i++)
            {
                Vector2 p1 = { m_points[i].x, m_points[i].y * -1 };
                Vector2 p2 = { m_points[i + 1].x, m_points[i + 1].y * -1 };
                //transform

                //scale
                p1 = p1 * scale;
                p2 = p2 * scale;
                //rotate
                p1 = Vector2::Rotate(p1, angle);
                p2 = Vector2::Rotate(p2, angle);
                //translate
                p1 += position;
                p2 += position;



                graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
            }
        }

	void Shape::Draw(Core::Graphics& graphics, const Transform& transform) {
		Draw(graphics, transform.position, transform.scale, transform.angle);
	}
}