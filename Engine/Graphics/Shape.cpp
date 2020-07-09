
#include "pch.h"
#include "Shape.h"
#include <fstream>

bool gk::Shape::Load(const std::string& filename)
{
	bool success = false;
	
	std::ifstream stream(filename);
	if (stream.is_open()) 
	{ 
		success = true; 

		stream >> m_color;

		while (!stream.eof())
		{
			Vector2 point;
			stream >> point;

			if (!stream.eof()) m_points.push_back(point);
		}
		

		stream.close();
	}

	return success;
}

void gk::Shape::Draw(Core::Graphics& graphics, gk::Vector2 position, float scale, float angle)
{
	graphics.SetColor(m_color);

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		//Local / Object Space Points
		gk::Vector2 p1 = m_points[i];
		gk::Vector2 p2 = m_points[i + 1];

		//Transform
		//Scale
		p1 *= scale;
		p2 *= scale;

		//Rotation
		p1 = gk::Vector2::rotate(p1, angle);
		p2 = gk::Vector2::rotate(p2, angle);

		//Translate
		p1 += position;
		p2 += position;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void gk::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	Draw(graphics, transform.position, transform.scale, transform.angle);
}
