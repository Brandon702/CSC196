#include "Player.h"
#include "Math/Math.h"
#include <fstream>

bool Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		stream >> m_transform;
		std::string shapename;
		stream >> (shapename);
		m_shape.Load(shapename);

		success = true;
	}

	return success;
}

void Player::Update(float dt)
{
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	//force = force + nc::Vector2{ 0, 100 }; //Gravity
	//Central Gravity
	nc::Vector2 direction = nc::Vector2{ 800, 450 } - m_transform.position;
	if (direction.Length() <= 200.0f)
	{
		float strength = 1.0f - (direction.Length() / 200.0f);
		direction.Normalize();
		force = force + (direction * 200.0f * strength);
	}

	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.98f;
	m_transform.position = m_transform.position + (m_velocity * dt);
	direction.Normalize();

	if (m_transform.position.x > 1600) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 1600;
	if (m_transform.position.y > 900) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 900;

	if (Core::Input::IsPressed('Q')) m_transform.angle -= dt * nc::DegreesToRadians(360.0f);
	if (Core::Input::IsPressed('E')) m_transform.angle += dt * nc::DegreesToRadians(360.0f);

	m_transform.Update();
}
