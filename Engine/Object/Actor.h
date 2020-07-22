#pragma once

#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Scene.h"
#include "core.h"

namespace gk
{
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
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {}
		virtual ~Actor() {}

		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		float GetRadius();

		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform() { return m_transform; }
		Shape& GetShape() { return m_shape; }
		
		void SetDestroy(bool destroy = true) { m_destroy = destroy; }
		bool IsDestroy() { return m_destroy; }

	protected:
		bool m_destroy{ false };
		Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;
	};
}
