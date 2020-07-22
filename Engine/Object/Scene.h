#pragma once
#include "core.h"
#include "pch.h"

namespace nc
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);
		
		template<typename T>
		T* GetActor()
		{
 			T* actor{ nullptr };
			for (nc::Actor* a : m_actors)
			{
				actor = dynamic_cast<T*>(a);
				if (actor) break;
			}
			return actor;
		}

		template<typename T>
		std::vector<T*> GetActors()
		{
			std::vector<T*> actors;
			for (nc::Actor* a : m_actors)
			{
				T* actor = dynamic_cast<T*>(a);
				if (actor)
				{
					actors.push_back(actor);
				}
			}
			return actors;
		}

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* object);

	private:
		std::list<class Actor*> m_actors;
	};
}
