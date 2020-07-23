#pragma once
#include "core.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"

namespace nc
{
	class Scene; //Forward Declaration

	class Actor
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform(transform), m_shape(shape) {}
		~Actor() {}

		virtual eType GetType() = 0;
		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);
		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		float GetRadius();

		bool IsDestory() { return m_destory; }
		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform() { return m_transform; }
		Shape& GetShape() { return m_shape; }

	protected:
		bool m_destory{ false };
		Scene* m_scene{nullptr};
		Transform m_transform;
		Shape m_shape;
	};
}
