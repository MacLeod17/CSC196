#pragma once

#include "core.h"
#include <vector>
#include <list>

class Game;

namespace gk
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* actor);

		void SetGame(class Game* game) { m_game = game; }
		Game* GetGame() { return m_game; }

		template <typename T>
		T* GetActor() 
		{
			T* result{ nullptr };

			for (Actor* actor : m_actors)
			{
				result = dynamic_cast<T*>(actor);
				if (result) { break; }
			}

			return result;
		}

		template <typename T>
		std::vector<T*> GetActors() 
		{
			std::vector<T*> results;

			for (Actor* actor : m_actors)
			{
				T* result = dynamic_cast<T*>(actor);
				if (result)
				{
					results.push_back(result);
				}
			}

			return results;
		}

	private:
		Game* m_game{ nullptr };
		std::list<class Actor*> m_actors;
	};
}
