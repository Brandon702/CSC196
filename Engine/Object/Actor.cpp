#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace nc
{
	bool Actor::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			stream >> m_transform;
			std::string shapename;
			std::getline(stream, shapename);
			m_shape.Load(shapename);

			success = true;
		}

		return success;
	}

	void Actor::Load(std::istream& stream)
	{
		stream >> m_transform;
		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);
	}

	void Actor::Update(float dt)
	{

	}
	void Actor::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}
}
