
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <string>

std::vector<gk::Vector2> classShape = { {0, -3}, {3, 3}, {0, 1}, {-3, 3}, {0, -3} }; // Triangle-ish shape used as class
std::vector<gk::Vector2> myShape = { {0, -5}, {3, 3}, {3, 6}, {0, 2}, {0, 6}, {2, 12}, {0, 10}, {-2, 12}, {0, 6}, {0, 2}, {-3, 6}, {-3, 3}, {0, -5} }; // My shape

gk::Color color{ 0, 1, 1 };
gk::Shape shape{ myShape, color };

gk::Vector2 position{ 400.0f, 300.0f };
float scale = 4.0f;
float angle = 0.0f;
float speed = 300.0f;

float frametime;

bool Update(float dt) // dt = Delta Time
{
	frametime = dt;
	
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	//int x;
	//int y;
	//Core::Input::GetMousePos(x, y);
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
	
	shape.Draw(graphics, position, scale, angle);
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

