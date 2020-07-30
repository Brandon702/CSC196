/*
TODO:
Looping Music

Bugs:
New enemies spawn at same spot
random only runs once on enemy spawning

Extra features:
Linear enemy spawning
2nd enemy type
Incrementing score
*/
#include "Game.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Locator.h"
#include "Actors/Projectile.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include <iostream>
#include <string>
#include <list>

float exponTimer = 3.0f;
float exponTimer2 = 5.0f;
float m_spawnTimer2 = 0;

void Game::Initalize()
{
	m_scene.Startup();
	m_scene.SetGame(this);
	g_particleSystem.Startup();
	g_audioSystem.Startup();
	g_audioSystem.AddAudio("Laser", "Laser.wav");
	g_audioSystem.AddAudio("Explosion", "Explosion.wav");
}

bool Game::Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			//Init game variables
			m_score = 0;
			m_lives = 3;
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::START_GAME:
	{
		g_audioSystem.StopLoopChannel();
		nc::Actor* player = new Player;
		player->Load("player.txt");
		m_scene.AddActor(player);

		Locator* locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ 3, 2 };
		//locator->GetTransform().angle = nc::DegreesToRadians(90);
		player->AddChild(locator);

		locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ -3, 2 };
		//locator->GetTransform().angle = nc::DegreesToRadians(90);
		player->AddChild(locator);

		for (size_t i = 0; i < 5; i++)
		{
			nc::Actor* actor = new Enemy;
			actor->Load("enemy.txt");
			Enemy* enemy = dynamic_cast<Enemy*>(actor);
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->SetSpeed(nc::random(40, 120));
			float distance = nc::random(600, 900);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = nc::Vector2::Rotate({0.0f,distance}, angle);

			actor->GetTransform().position = m_scene.GetActor<Player>()->GetTransform().position + position;
			m_scene.AddActor(actor);
		}
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
		m_spawnTimer += dt;
		m_spawnTimer2 += dt;
		m_frameTime = dt;
		if (m_spawnTimer >= exponTimer)
		{
			m_spawnTimer = 0;
			exponTimer -= 0.1f;
			if (exponTimer < 0.1f)
			{
				exponTimer = 0.1f;
			}
			for (size_t i = 0; i < nc::random(1, 3); i++)
			{
				Enemy* enemy = new Enemy;
				enemy->Load("enemy.txt");
				enemy->SetTarget(m_scene.GetActor<Player>());
				enemy->SetSpeed(nc::random(40, 120));
				enemy->SetScore(m_value += 5);
				float distance = nc::random(500, 800);
				float angle = nc::random(0, nc::TWO_PI);
				m_scene.AddActor(enemy);
			}
		}
		
		if (m_score >= 0)
		{
			if (m_spawnTimer2 >= exponTimer2)
			{
				m_spawnTimer2 = 0;
				exponTimer2 -= 0.05f;
				if (exponTimer2 < 0.3f)
				{
					exponTimer2 = 0.3f;
				}
				for (size_t i = 0; i < nc::random(1, 3); i++)
				{
					Enemy* enemy2 = new Enemy;
					enemy2->Load("enemy2.txt");
					enemy2->SetTarget(m_scene.GetActor<Player>());
					enemy2->SetSpeed(nc::random(120, 240));
					enemy2->SetScore(m_value += 5);
					float distance = nc::random(600, 800);
					float angle = nc::random(0, nc::TWO_PI);
					m_scene.AddActor(enemy2);
				}
			}
		}
		
		if (m_score > m_highScore) m_highScore = m_score;
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_stateTimer = 0;
			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
		}
		break;
	case Game::eState::PLAYER_DEAD:
		m_lives = m_lives - 1;
		exponTimer = 3.0f;
		exponTimer2 = 5.0f;
		m_spawnTimer2 = 0;
		m_state = (m_lives == 0) ? eState::GAME_OVER : eState::GAME_WAIT;
		m_stateTimer = 3;
		break;
	case Game::eState::GAME_WAIT:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::START_GAME;
		}
		break;
	default:
		break;
	}


	int x, y;
	Core::Input::GetMousePos(x, y);

	m_scene.Update(dt);
	g_particleSystem.Update(dt);
	g_audioSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1, 1, 1 });
	switch (m_state)
	{
	case Game::eState::TITLE:
		graphics.DrawString(800, 450, "Vectrex");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
	{
		break;
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
	std::string score = "Score: " + std::to_string(m_score);
	graphics.DrawString(1300, 10, score.c_str());
	std::string lives = "Lives: " + std::to_string(m_lives);
	graphics.DrawString(50, 10, lives.c_str());

	m_scene.Draw(graphics);
	g_particleSystem.Draw(graphics);
}
