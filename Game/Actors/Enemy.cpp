#include "Enemy.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
#include <fstream>

bool Enemy::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		stream >> m_transform;
		std::string shapename;
		stream >> (shapename);
		m_shape.Load(shapename);
		stream.close();
		success = true;
	}

	return success;
}

void Enemy::Update(float dt)
{
	nc::Vector2 targetPosition = (m_target) ? m_target->GetTransform().position : nc::Vector2{ 800, 450 };
	nc::Vector2 direction = targetPosition - m_transform.position;
	direction.Normalize();
	nc::Vector2 velocity = direction * m_speed;
	m_transform.position = m_transform.position + (velocity * dt);
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);

	m_transform.Update();
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PROJECTILE)
	{
		g_audioSystem.PlayAudio("Explosion");
		m_destroy = true;

		//set game points / score
		m_scene->GetGame()->AddPoints(m_value);

		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::green, {1,0.5,0 } };
		nc::Color color = colors[rand() % 4];
		g_particleSystem.Create({ m_transform.position }, 0, 180, 40, 1.5, color, 100, 200);

	}
}
