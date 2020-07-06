#pragma once

#include "core.h"
#include "../Math/Color.h"
#include "../Math/Vector2.h"
#include <vector>


namespace gk
{
	class Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<Vector2>& points, const Color& color) 
		{
			m_points = points;
			SetColor(color);
		}

		void Draw(Core::Graphics& graphics, Vector2 position, float scale = 1.0f, float angle = 0.0f);

		void SetColor(Color color);
		const Color& GetColor() const
		{
			return m_color;
		}

	private:
		std::vector<Vector2> m_points;
		Color m_color;
	};

}