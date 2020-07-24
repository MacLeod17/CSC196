
#include "core.h"
#include "Game.h"

Game game;

bool Update(float dt) // dt = Delta Time
{
	bool quit = game.Update(dt);
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int main()
{
	game.Startup();
	
	char name[] = "Kilpack";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}
