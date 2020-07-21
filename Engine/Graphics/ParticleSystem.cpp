#include "pch.h"
#include "ParticleSystem.h"
#include "Math/Random.h"
#include "Math/Math.h"

void nc::ParticleSystem::Startup()
{
	m_size = 3000;
	m_particles = new Particle[m_size];
}

void nc::ParticleSystem::Shutdown()
{
	delete[] m_particles;
}

void nc::ParticleSystem::Update(float dt)
{
	for (size_t i = 0; i < m_size; i++)
	{
		Particle* p = &m_particles[i];
		if (p->active)
		{
			p->lifetime = p->lifetime - dt;
			p->active = (p->lifetime > 0);

			p->prevPosition = p->position;
			p->position = p->position + (p->velocity * dt);
		}
	}
}

void nc::ParticleSystem::Draw(Core::Graphics& graphics)
{
	for (size_t i = 0; i < m_size; i++)
	{
		Particle* p = &m_particles[i];
		if (p->active)
		{
			graphics.SetColor(p->color);
			graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
		}
	}
}

void nc::ParticleSystem::Create(const Vector2& position, 
	float angle, 
	float angleRange, 
	size_t count, 
	float lifetime, 
	const Color& color, 
	float minSpeed, 
	float maxSpeed)
{
	for (size_t i = 0; i < count; i++)
	{
		Particle* p = GetFreeParticle();
		if (p)
		{
			p->active = true;
			p->lifetime = lifetime;
			p->position = position;
			p->prevPosition = position;
			p->color = color;

			float angleRandom = nc::DegreesToRadians(nc::random(-angleRange, angleRange));
			Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, angle + angleRandom);
			p->velocity = direction * nc::random(minSpeed, maxSpeed);
		}
	}
}

nc::Particle* nc::ParticleSystem::GetFreeParticle()
{

	for (size_t i = 0; i < m_size; i++)
	{
		Particle* p = &m_particles[i];
		if (!p->active)
		{
			return p;
		}
	}
	return nullptr;
}
