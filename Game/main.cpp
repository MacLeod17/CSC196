
#include "core.h"
#include "Graphics/Shape.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>

gk::Player player;
gk::Enemy enemy;

float t{ 0 };

float frametime;
float roundtime{ 0 };
bool gameover{ false };

DWORD prevtime;
DWORD deltatime;

bool Update(float dt) // dt = Delta Time
{
	DWORD time = GetTickCount();
	deltatime = time - prevtime; //Current frame time / Previous frame time
	prevtime = time;
	
	t += dt * 5.0f;

	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	player.Update(dt);
	enemy.Update(dt);
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltatime / 1000.0f).c_str());

	//float v = (std::sin(t) + 1.0f) * 0.5f;
	//gk::Color c = gk::Lerp(gk::Color{ 0, 0, 1 }, gk::Color{ 1, 0, 0 }, v);
	//graphics.SetColor(c);
	//gk::Vector2 p = gk::Lerp(gk::Vector2{ 400, 300 }, gk::Vector2{ 400, 100 }, v);
	//graphics.DrawString(p.x, p.y, "Last Starfighter");

	if (gameover) graphics.DrawString(400, 300, "Game Over");

	player.Draw(graphics);
	enemy.Draw(graphics);
}

int main()
{
	DWORD ticks = GetTickCount(); //How many ticks in a second
	std::cout << ticks / 1000 / 60 / 60 / 24 << std::endl;
	prevtime = GetTickCount();

	player.Load("player.txt");
	enemy.Load("enemy.txt");
	enemy.SetTarget(&player);

	char name[] = "Kilpack";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
