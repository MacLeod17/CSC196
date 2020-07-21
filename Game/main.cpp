
#include "core.h"
#include "Graphics/Shape.h"
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

	scene.Update(dt);
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());

	//float v = (std::sin(t) + 1.0f) * 0.5f;
	//gk::Color c = gk::Lerp(gk::Color{ 0, 0, 1 }, gk::Color{ 1, 0, 0 }, v);
	//graphics.SetColor(c);
	//gk::Vector2 p = gk::Lerp(gk::Vector2{ 400, 300 }, gk::Vector2{ 400, 100 }, v);
	//graphics.DrawString(p.x, p.y, "Last Starfighter");

	scene.Draw(graphics);
}

int main()
{
	scene.Startup();
	
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
}
