
#include "pch.h"
#include "Shape.h"
#include "Math/Matrix22.h"
#include <fstream>

bool gk::Shape::Load(const std::string& filename)
{
	bool success = false;
	
	std::ifstream stream(filename);
	if (stream.is_open()) 
	{ 
		success = true; 

		stream >> m_color;

		//Get # of Points
		std::string line;
		getline(stream, line);
		size_t size = stoi(line);

		//Read Points
		for (size_t i = 0; i < size; i++)
		{
			Vector2 v;
			stream >> v;
			m_points.push_back(v);
		}

		stream.close();
	}

	return success;
}

void gk::Shape::Draw(Core::Graphics& graphics, gk::Vector2 position, float scale, float angle)
{
	graphics.SetColor(m_color);

	Matrix22 mxScale;
	mxScale.Scale(scale);
	Matrix22 mxRotate;
	mxRotate.Rotate(angle);

	Matrix22 mx = mxScale * mxRotate;

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		//Local / Object Space Points
		gk::Vector2 p1 = m_points[i];
		gk::Vector2 p2 = m_points[i + 1];

		//Transform
		//Scale / Rotate
		p1 = p1 * mx;
		p2 = p2 * mx;

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
