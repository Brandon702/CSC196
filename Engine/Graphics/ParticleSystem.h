#pragma once
#include "core.h"
#include "Particle.h"

namespace nc
{
	class ParticleSystem
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void Create(const Vector2& position,
			float angle,
			float angleRange,
			size_t count,
			float lifetime,
			const Color& color,
			float minSpeed,
			float maxSpeed);

	protected:
		Particle* GetFreeParticle();

	protected:
		Particle* m_particles;
		size_t m_size;
	};
}

extern nc::ParticleSystem g_particleSystem;