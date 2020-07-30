#include "Player.h"
#include "Enemy.h"
#include "Math/Math.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "../Game.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Math/Random.h"
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
	m_fireTimer += dt;
	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;
		g_audioSystem.PlayAudio("Laser");
		Projectile* projectile = new Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);
	}

	nc::Vector2 force; // 0,0
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	//force = force + nc::Vector2{ 0, 100 }; //Gravity
	//Central Gravity
	nc::Vector2 direction = nc::Vector2{ 800, 450 } -m_transform.position;
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

	float torque{ 0 };
	if (Core::Input::IsPressed('Q')) torque = -20.0f;
	if (Core::Input::IsPressed('E')) torque = 20.0f;

	m_anglarVelocity = m_anglarVelocity + (torque * dt);
	m_anglarVelocity = m_anglarVelocity * 0.9f;
	m_transform.angle = m_transform.angle + (m_anglarVelocity * dt);

	if (force.LengthSqr() > 0)
	{
		Actor* child = m_children[0];
		g_particleSystem.Create(child->GetTransform().matrix.GetPosition(),
								child->GetTransform().matrix.GetAngle() + nc::PI,
								10, 1, 1, nc::Color(1, 0.5, 0), 100, 200);

		child = m_children[1];
		g_particleSystem.Create(child->GetTransform().matrix.GetPosition(),
			child->GetTransform().matrix.GetAngle() + nc::PI,
			10, 1, 1, nc::Color(1, 0.5, 0), 100, 200);
	}

	if (Core::Input::IsPressed('F') && !m_prevButtonPress)
	{
		m_transform.position = nc::Vector2{ nc::random(0,1600), nc::random(0,900) };
		m_transform.angle = nc::random(0, nc::TWO_PI);
	}

	m_prevButtonPress = Core::Input::IsPressed('F');

	m_transform.Update();

	//Update Children
	for (auto child : m_children)
	{
		child->Update(dt);
	}
}

void Player::OnCollision(Actor* actor)
{
	if (!m_destroy && actor->GetType() == eType::ENEMY)
	{
		m_destroy = true;
		m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);

		//Set target null
		auto enemies = m_scene->GetActors<Enemy>();
		for (auto enemy : enemies)
		{
			enemy->SetTarget(nullptr);
		}

		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::green, {1,0.5,0 } };
		nc::Color color = colors[rand() % 4];
		g_particleSystem.Create({ m_transform.position }, 0, 180, 40, 1.5, color, 100, 200);
	}
}
