
#include "core.h"
#include "Graphics/Shape.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Object/Actor.h"
#include <iostream>
#include <string>

gk::Shape shape;
gk::Transform transform{ { 400, 300 }, 4, 0 };

gk::Actor player;
gk::Actor enemy;

float t{ 0 };

float speed = 300.0f;
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
	
	t += dt * 3.0f;

	frametime = dt;
	roundtime += dt;

	if (roundtime >= 5.0f) gameover = true;
	if (gameover) dt = 0;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	gk::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = gk::Vector2::forward * speed * dt; }
	gk::Vector2 direction = force;

	//direction = gk::Vector2::rotate(direction, transform.angle);
	//transform.position += direction;

	direction = gk::Vector2::rotate(direction, player.GetTransform().angle);
	player.GetTransform().position += direction;

	//Rotate
	if (Core::Input::IsPressed('A')) { player.GetTransform().angle -= (dt * gk::DegreesToRadians(360.0f)); }
	if (Core::Input::IsPressed('D')) { player.GetTransform().angle += (dt * gk::DegreesToRadians(360.0f)); }
	//if (Core::Input::IsPressed('A')) { transform.angle -= (dt * gk::DegreesToRadians(360.0f)); }
	//if (Core::Input::IsPressed('D')) { transform.angle += (dt * gk::DegreesToRadians(360.0f)); }
	
	player.GetTransform().position = gk::Clamp(player.GetTransform().position, { 0, 0 }, { 800, 600 });
	//transform.position = gk::Clamp(transform.position, { 0, 0 }, { 800, 600 });

	//Translate
	//if (Core::Input::IsPressed('A')) { position += gk::Vector2::left * speed * dt; }
	//if (Core::Input::IsPressed('D')) { position += gk::Vector2::right * speed * dt; }
	
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
	//shape.Draw(graphics, transform);
}

int main()
{
	DWORD ticks = GetTickCount(); //How many ticks in a second
	std::cout << ticks / 1000 / 60 / 60 / 24 << std::endl;
	prevtime = GetTickCount();

	//shape.Load("playershape.txt");
	player.Load("player.txt");
	enemy.Load("enemy.txt");

	char name[] = "Kilpack";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}

