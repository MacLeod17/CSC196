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
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {}
		virtual ~Actor() {}

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		void Draw(Core::Graphics& graphics);

		Transform& GetTransform() { return m_transform; }
		Shape& GetShape() { return m_shape; }
		Scene& GetScene() { return m_scene; }

	protected:
		Transform m_transform;
		Shape m_shape;
		Scene m_scene;
	};
}
