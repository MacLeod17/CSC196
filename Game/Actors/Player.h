#pragma once

#include "Object/Actor.h"

namespace gk
{
	class Player : public Actor
	{
	public:
		Player() {}
		virtual ~Player() {}
	
		bool Load(const std::string& filename) override;

		void Update(float dt) override;

	protected:
		gk::Vector2 m_velocity{ 0, 0 };
		float m_thrust{ 0.0f };
		float m_rotationRate{ 0.0f };
	};
}
