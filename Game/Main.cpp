#include "core.h"
#include "Game.h"

Game game;

bool Update(float dt) //dt = (1/60) = 0.1667 | (1/90) = 0.0111
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
	game.Initalize();

	char name[] = "CSC196";
	Core::Init(name, 1600, 900, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	//g_particleSystem.Shutdown();
	//scene.Shutdown();
}