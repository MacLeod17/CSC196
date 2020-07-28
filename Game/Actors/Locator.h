#pragma once

#include "Object/Actor.h"

namespace gk
{
	class Locator : public Actor
	{
	public:
		Locator() {}
		virtual ~Locator() {}

		virtual eType GetType() { return eType::LOCATOR; }

		virtual void Update(float dt) override;
	};
}