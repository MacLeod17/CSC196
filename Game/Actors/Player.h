#pragma once

#include "Object/Actor.h"

namespace gk
{
	class Player : public Actor
	{
	public:
		Player() {}
		virtual ~Player() {}
	
		virtual eType GetType() { return eType::PLAYER; }

		bool Load(const std::string& filename) override;
		void Update(float dt) override;

	protected:
		Vector2 m_velocity{ 0, 0 };
		float m_thrust{ 0.0f };
		float m_rotationRate{ 0.0f };
		float m_fireRate{ 0.2f };
		float m_fireTimer{ 0.0f };
	};
}
