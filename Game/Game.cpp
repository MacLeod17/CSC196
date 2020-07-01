
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include <iostream>

gk::Vector2 position{ 400, 300 };
std::vector<gk::Vector2> points;

bool Update(float dt)
{
	return false;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	for (size_t i = 0; i < 40 - 1; i++)
	{
		gk::Vector2 p1 = points[i];
		gk::Vector2 p2 = points[i+1];
		
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	for (size_t i = 0; i < 40; i++)
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

