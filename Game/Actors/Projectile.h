#pragma once

#include "Object/Actor.h"

namespace gk
{
	class Projectile : public Actor
	{
	public:
		Projectile() {}
		virtual ~Projectile() {}
		
		virtual eType GetType() { return eType::PROJECTILE; }

		virtual bool Load(const std::string& filename) override;
		virtual void Update(float dt) override;

		virtual void OnCollision(Actor* actor);

		void SetThrust(float thrust) { m_thrust = thrust; }

	protected:
		float m_thrust{ 0 };
		float m_lifetime{ 3 };
	};
}
