
#include "pch.h"
#include "Shape.h"
#include "Math/Matrix33.h"
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

	Matrix33 mxScale;
	mxScale.Scale(scale);

	Matrix33 mxRotate;
	mxRotate.Rotate(angle);

	Matrix33 mxTranslate;
	mxTranslate.Translate(position);

	Matrix33 mx = mxScale * mxRotate * mxTranslate;

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		//Local / Object Space Points
		Vector2 p1 = m_points[i];
		Vector2 p2 = m_points[i + 1];

		//Transform
		//Scale / Rotate / Translate
		p1 = p1 * mx;
		p2 = p2 * mx;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void gk::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	graphics.SetColor(m_color);

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		//Local / Object Space Points
		Vector2 p1 = m_points[i];
		Vector2 p2 = m_points[i + 1];

		//Transform
		//Scale / Rotate / Translate
		p1 = p1 * transform.matrix;
		p2 = p2 * transform.matrix;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}
