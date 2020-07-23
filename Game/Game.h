#pragma once
#include <core.h>
#include "Object\Scene.h"


class Game
{
public:
	enum class eState
	{
		TITLE,
		START_GAME,
		GAME,
		GAME_OVER
	};

public:
	void Initalize();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	void AddPoints(int points) { m_score += points; }
	void SetState(eState state) { m_state = state; }

protected:
	eState m_state{ eState::TITLE };

	int m_score{ 0 };
	int m_live{ 3 };
	int m_highScore{ 0 };

	nc::Scene m_scene;

	float m_frameTime;
	float m_spawnTimer{ 0 };
	float m_stateTimer{ 0 };

};

