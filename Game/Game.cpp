/*
TODO:
Spacebar doesnt delete enemies
Exception on enemy spawn
*/
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>
#include <list>

std::list<nc::Actor*> sceneActors;

float frameTime;
DWORD prevTime;
DWORD deltaTime;
float roundTime{ 0 };
bool gameOver = { false };
float spawnTimer{ 0 };

template<typename T>
T* GetActor()
{
	T* actor{ nullptr };
	for (nc::Actor* a : sceneActors)
	{
		actor = dynamic_cast<T*>(a);
		if (actor) break;
	}
	return actor;
}

template<typename T>
std::vector<T*> GetActors()
{
	std::vector<T*> actors;
	for (nc::Actor* a : sceneActors)
	{
		T* actor = dynamic_cast<T*>(a);
		if (actor)
		{
			actors.push_back(actor);
		}
	}
	return actors;
}

void removeActor(nc::Actor* actor)
{
	auto iter = std::find(sceneActors.begin(), sceneActors.end(), actor);
	if (iter != sceneActors.end())
	{
		delete* iter;
		sceneActors.erase(iter);
	}
}

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
		enemy->SetTarget(GetActor<Player>());
		enemy->SetSpeed(nc::random(40, 90));
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 1600), nc::random(0, 900) };
		sceneActors.push_back(enemy);

	}

	if (Core::Input::IsPressed(VK_SPACE))
	{
		auto enemy = GetActor<Enemy>();
		removeActor(enemy);
	}
	
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	int x, y;
	Core::Input::GetMousePos(x, y);

	for (nc::Actor* actor : sceneActors)
	{
		actor->Update(dt);
	}
	
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1, 1, 1 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 25, std::to_string(1.0f/frameTime).c_str());
	graphics.DrawString(10, 40, std::to_string(deltaTime/1000.f).c_str());
	if (gameOver) graphics.DrawString(800, 450, "Game Over");

	for (nc::Actor* actor : sceneActors)
	{
		actor->Draw(graphics);
	}
}

int main()
{
	// Initialize
	nc::Actor* player = new Player;
	Player* e = dynamic_cast<Player*>(player);
	player->Load("player.txt");
	sceneActors.push_back(player);

	for (size_t i = 0; i < 3; i++)
	{
		nc::Actor* actor = new Enemy;
		actor->Load("enemy.txt");
		Enemy* enemy = dynamic_cast<Enemy*>(actor);
		enemy->SetTarget(player);
		enemy->SetSpeed(nc::random(40, 90));
		actor->GetTransform().position = nc::Vector2{ nc::random(0, 1600), nc::random(0, 900) };
		sceneActors.push_back(actor);
	}


	char name[] = "CSC196";
	Core::Init(name, 1600, 900, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
