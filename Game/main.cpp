
#include "core.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Object/Actor.h"
#include "Object/Scene.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

gk::Scene scene;

float frametime;
float spawntimer{ 0 };

bool Update(float dt) // dt = Delta Time
{
	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	//if (Core::Input::IsPressed(VK_SPACE))
	//{
	//	auto removeActors = scene.GetActors<gk::Enemy>();
	//	for (auto actor : removeActors)
	//	{
	//		scene.RemoveActor(actor);
	//	}
	//}

	spawntimer += dt;
	if (spawntimer >= 3.0f)
	{
		spawntimer = 0.0f;

		//Add Enemy to Scene
		gk::Enemy* enemy = new gk::Enemy;
		enemy->Load("enemy.txt");
		enemy->SetTarget(scene.GetActor<gk::Player>());
		enemy->GetTransform().position = gk::Vector2{ gk::random(0, 800), gk::random(0, 600) };
		enemy->SetThrust(gk::random(50, 150));
		scene.AddActor(enemy);
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		gk::Color colors[] = { gk::Color::white, gk::Color::red, gk::Color::green, gk::Color::blue, gk::Color::yellow };
		gk::Color color = colors[(int)gk::random(0, 4)];

		g_particleSystem.Create(gk::Vector2{ x, y }, 0, 180, 30, color, 1, 100, 200);
	}

	g_particleSystem.Update(dt);
	scene.Update(dt);
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());

	g_particleSystem.Draw(graphics);
	scene.Draw(graphics);
}

int main()
{
	scene.Startup();
	g_particleSystem.Startup();
	
	gk::Player* player = new gk::Player;
	player->Load("player.txt");
	scene.AddActor(player);

	for (int i = 0; i < 3; i++)
	{
		gk::Enemy* enemy = new gk::Enemy;
		enemy->Load("enemy.txt");
		enemy->SetTarget(player);
		enemy->GetTransform().position = gk::Vector2{ gk::random(0, 800), gk::random(0, 600) };
		enemy->SetThrust(gk::random(50, 150));
		scene.AddActor(enemy);
	}

	char name[] = "Kilpack";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	scene.Shutdown();
	g_particleSystem.Shutdown();
}
