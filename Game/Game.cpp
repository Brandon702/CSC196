/*
TODO:
*/
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Object/Scene.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <list>

nc::Scene scene;
nc::ParticleSystem particleSystem;

float frameTime;
DWORD prevTime;
DWORD deltaTime;
float roundTime{ 0 };
bool gameOver = { false };
float spawnTimer{ 0 };

bool Update(float dt) //dt = (1/60) = 0.1667 | (1/90) = 0.0111
{
	frameTime = dt;
	spawnTimer += dt;
	if (spawnTimer >= 3.0f)
	{
		spawnTimer = 0;

		//Enemy* e = dynamic_cast<Enemy*>(GetActor<Enemy>());

		//Spawn enemy
		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		enemy->SetTarget(scene.GetActor<Player>());
		enemy->SetSpeed(nc::random(40, 90));
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 1600), nc::random(0, 900) };
		//sceneActors.push_back(enemy);
		scene.AddActor(enemy);

	}
	/*
	if (Core::Input::IsPressed(VK_SPACE))
	{
		auto enemy = GetActor<Enemy>();
		removeActor(enemy);
	}
	*/
	
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	Player* player = scene.GetActor<Player>();
	particleSystem.Create(player->GetTransform().position, player->GetTransform().angle + nc::PI, 10, 1, 1, nc::Color(1, 0.5, 0), 100, 200);
	
	int x, y;
	Core::Input::GetMousePos(x, y);
	
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::green, {1,0.5,0 } };
		nc::Color color = colors[rand() % 4];

		particleSystem.Create({x,y}, 0, 180, 40, 1.5, color, 100, 200);
	}

	scene.Update(dt);
	particleSystem.Update(dt);
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1, 1, 1 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 25, std::to_string(1.0f/frameTime).c_str());
	graphics.DrawString(10, 40, std::to_string(deltaTime/1000.f).c_str());
	if (gameOver) graphics.DrawString(800, 450, "Game Over");
	
	particleSystem.Draw(graphics);
	scene.Draw(graphics);
	
}

int main()
{
	scene.Startup();
	particleSystem.Startup();
	// Initialize
	nc::Actor* player = new Player;
	player->Load("player.txt");
	scene.AddActor(player);

	for (size_t i = 0; i < 3; i++)
	{
		nc::Actor* actor = new Enemy;
		actor->Load("enemy.txt");
		Enemy* enemy = dynamic_cast<Enemy*>(actor);
		enemy->SetTarget(player);
		enemy->SetSpeed(nc::random(40, 90));
		actor->GetTransform().position = nc::Vector2{ nc::random(0, 1600), nc::random(0, 900) };
		scene.AddActor(actor);
	}


	char name[] = "CSC196";
	Core::Init(name, 1600, 900, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	particleSystem.Shutdown();
	scene.Shutdown();
}
