
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <iostream>

const size_t NUM_POINTS = 40;
float speed = 5.0f;

std::vector<gk::Vector2> points = { {0, -3}, {3, 3}, {0, 1}, {-3, 3}, {0, -3} }; // Triangle-ish shape used as class
gk::Color color{ 0, 1, 1 };
 
gk::Vector2 position{ 400.0f, 300.0f };
float scale = 4.0f;
float angle = 0.0f;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	gk::Vector2 target = gk::Vector2{ x, y };
	gk::Vector2 direction = target - position;
	direction.normalize();

	if (Core::Input::IsPressed('A')) { angle -= dt; }
	if (Core::Input::IsPressed('D')) { angle += dt; }
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(color);
	
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		//Local / Object Space Points
		gk::Vector2 p1 = points[i];
		gk::Vector2 p2 = points[i+1];

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

int main()
{
	char name[] = "Kilpack";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}

