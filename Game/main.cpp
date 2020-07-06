
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <iostream>
#include <string>

const size_t NUM_POINTS = 40;
float speed = 300.0f;

std::vector<gk::Vector2> points = { {0, -3}, {3, 3}, {0, 1}, {-3, 3}, {0, -3} }; // Triangle-ish shape used as class
gk::Color color{ 0, 1, 1 };
 
gk::Vector2 position{ 400.0f, 300.0f };
float scale = 4.0f;
float angle = 0.0f;

float frametime;


bool Update(float dt) // dt = Delta Time
{
	frametime = dt;
	
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	//gk::Vector2 target = gk::Vector2{ x, y };
	//gk::Vector2 direction = target - position;
	//direction.normalize();

	gk::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = gk::Vector2::forward * speed * dt; }
	gk::Vector2 direction = force;
	direction = gk::Vector2::rotate(direction, angle);
	position += direction;

	//Rotate
	if (Core::Input::IsPressed('A')) { angle -= (dt * 3.0f); }
	if (Core::Input::IsPressed('D')) { angle += (dt * 3.0f); }
	
	//Translate
	//if (Core::Input::IsPressed('A')) { position += gk::Vector2::left * speed * dt; }
	//if (Core::Input::IsPressed('D')) { position += gk::Vector2::right * speed * dt; }
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	
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
	DWORD ticks = GetTickCount(); //How many ticks in a second
	std::cout << ticks / 1000 / 60 / 60 / 24 << std::endl;
	
	char name[] = "Kilpack";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}

