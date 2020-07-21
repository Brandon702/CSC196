#include "Projectile.h"
#include "Math/Math.h"
#include <fstream>

bool Projectile::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		stream >> m_transform;
		std::string shapename;
		std::getline(stream, shapename);
		m_shape.Load(shapename);
	}

	return success;
}

void Projectile::Update(float dt)
{
	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
	nc::Vector2 velocity = direction * m_speed;
	m_transform.position = m_transform.position + (velocity * dt);
	m_transform.Update();
}
/*
void Projectile::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		m_destroy = true;
	}
}
*/