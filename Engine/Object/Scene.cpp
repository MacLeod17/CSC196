
#include "pch.h"
#include "Scene.h"
#include "Actor.h"

namespace gk
{
	void Scene::Startup()
	{
		// nothing
	}

	void Scene::Shutdown()
	{
		for (Actor* actor : m_actors)
		{
			delete actor;
		}

		m_actors.clear();
	}

	void Scene::Update(float dt)
	{
		for (Actor* actor : m_actors)
		{
			actor->Update(dt);
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		for (Actor* actor : m_actors)
		{
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(Actor* actor)
	{
		actor->GetScene() = *this;
		m_actors.push_back(actor);
	}

	void Scene::RemoveActor(Actor* actor)
	{
		std::list<Actor*>::iterator iter = std::find(m_actors.begin(), m_actors.end(), actor);
		if (iter != m_actors.end())
		{
			delete* iter;
			m_actors.erase(iter);
		}
	}
}

