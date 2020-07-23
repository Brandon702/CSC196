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
	m_scene.SetGame(this);
	g_particleSystem.Startup();
}

bool Game::Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::START_GAME:
	{
		m_score = 0;
		//m_lives = 3;
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
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
		m_spawnTimer += dt;
		m_frameTime = dt;
		if (m_spawnTimer >= 3.0f)
		{
			m_spawnTimer = 0;
			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->SetSpeed(nc::random(40, 90));
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 1600), nc::random(0, 900) };
			m_scene.AddActor(enemy);
		}
		if (m_score > m_highScore) m_highScore = m_score;
		m_scene.Update(dt);
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer += dt;
		if (m_stateTimer >= 5)
		{
			m_stateTimer = 0;
			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
		}
		break;
	default:
		break;
	}


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

	
	g_particleSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1, 1, 1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 25, std::to_string(1.0f / m_frameTime).c_str());

	switch (m_state)
	{
	case Game::eState::TITLE:
		graphics.DrawString(800, 450, "VECTREX");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
	{
		std::string score = "Score: " + std::to_string(m_score);
		graphics.DrawString(1300, 10, score.c_str());
		m_scene.Draw(graphics);
	}
		break;
	case Game::eState::GAME_OVER:
		graphics.DrawString(800, 450, "Game Over");
		std::string tScore = "Total Score: " + std::to_string(m_score);
		graphics.DrawString(790, 500, tScore.c_str());
		break;
	}
	std::string hScore = "High Score: " + std::to_string(m_highScore);
	graphics.DrawString(800, 10, hScore.c_str());

	g_particleSystem.Draw(graphics);
}
