#include "pch.h"
#include "Shape.h"
#include "Math/Matrix33.h"
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

			//Read the number of points
			std::string line;
			std::getline(stream, line);
			size_t size = stoi(line);

			//Read points
			for (size_t i = 0; i < size; i++)
			{
				Vector2 point;
				stream >> point;

				m_points.push_back(point);
			}

			stream.close();
		}

		//Compute radius from point length
		m_radius = 0;
		for (size_t i = 0; i < m_points.size(); i++)
		{
			nc::Vector2 p1 = m_points[i];
			float length = p1.Length();
			
			if (length > m_radius) m_radius = length;
			m_radius = length;
		}

		return success;
	}
	void Shape::Draw(Core::Graphics& graphics, Vector2 position, float scale, float angle)
	{
		graphics.SetColor(m_color);

		nc::Matrix33 mxScale;
		mxScale.Scale(scale);
		nc::Matrix33 mxRotate;
		mxRotate.Rotate(angle);
		nc::Matrix33 mxTranslate;
		mxTranslate.Translate(position);

		nc::Matrix33 mx = mxScale * mxRotate;

		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			nc::Vector2 p1 = m_points[i];
			nc::Vector2 p2 = m_points[i + 1];
			//Scale/Rotate
			p1 = p1 * mx;
			p2 = p2 * mx;


			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Shape::Draw(Core::Graphics& graphics, const Transform& transform) {

		graphics.SetColor(m_color);
		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			//Draw(graphics, transform.position, transform.scale, transform.angle);
			nc::Vector2 p1 = m_points[i];
			nc::Vector2 p2 = m_points[i + 1];
			//Scale/Rotate/Translate
			p1 = p1 * transform.matrix;
			p2 = p2 * transform.matrix;
			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}