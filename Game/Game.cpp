#include "Game.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <list>

void Game::Initalize()
{
	m_scene.Startup();
	g_particleSystem.Startup();
	// Initialize
	nc::Actor* player = new Player;
	player->Load("player.txt");
	m_scene.AddActor(player);

	for (size_t i = 0; i < 3; i++)
	{
		nc::Actor* actor = new Enemy;
		actor->Load("enemy.txt");
		Enemy* enemy = dynamic_cast<Enemy*>(actor);
		enemy->SetTarget(player);
		enemy->SetSpeed(nc::random(40, 90));
		actor->GetTransform().position = nc::Vector2{ nc::random(0, 1600), nc::random(0, 900) };
		m_scene.AddActor(actor);
	}
}

bool Game::Update(float dt)
{
	m_frameTime = dt;
	m_spawnTimer += dt;
	if (m_spawnTimer >= 3.0f)
	{
		m_spawnTimer = 0;

		//Spawn enemy
		Enemy* enemy = new Enemy;
		enemy->Load("enemy.txt");
		enemy->SetTarget(m_scene.GetActor<Player>());
		enemy->SetSpeed(nc::random(40, 90));
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 1600), nc::random(0, 900) };
		//sceneActors.push_back(enemy);
		m_scene.AddActor(enemy);

	}

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);
	/*
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::green, {1,0.5,0 } };
		nc::Color color = colors[rand() % 4];
		g_particleSystem.Create({ x,y }, 0, 180, 40, 1.5, color, 100, 200);
	}
	*/

	m_scene.Update(dt);
	g_particleSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1, 1, 1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 25, std::to_string(1.0f / m_frameTime).c_str());
	//graphics.DrawString(10, 40, std::to_string(deltaTime / 1000.f).c_str());

	g_particleSystem.Draw(graphics);
	m_scene.Draw(graphics);
}
