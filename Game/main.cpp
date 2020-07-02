
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include <iostream>

const size_t NUM_POINTS = 40;
float speed = 5.0f;
std::vector<gk::Vector2> points;
gk::Vector2 position{ 400.0f, 300.0f };

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	gk::Vector2 target = gk::Vector2{ x, y };
	gk::Vector2 direction = target - position;
	direction.normalize();

	position += -direction * 5.0f;

	//if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position += gk::Vector2{ -1.0f, 0.0f } *speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += gk::Vector2{ 1.0f, 0.0f } *speed; }
	
	for (gk::Vector2& point : points)
	{
		point = gk::Vector2{ gk::random(-10.0f, 10.0f), gk::random(-10.0f, 10.0f) };
	}
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	
	for (size_t i = 0; i < NUM_POINTS - 1; i++)
	{
		gk::Vector2 p1 = position + points[i];
		gk::Vector2 p2 = position + points[i+1];
		
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	for (size_t i = 0; i < NUM_POINTS; i++)
	{
		points.push_back(gk::Vector2{ gk::random(0.0f, 600.0f), gk::random(0.0f, 800.0f) });
	}
	
	char name[] = "Kilpack";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

    std::cout << "Hello World!\n";
}

