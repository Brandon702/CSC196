#pragma once
#include <core.h>
#include "Object\Scene.h"


class Game
{
public:
	void Initalize();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

protected:
	int m_score{ 0 };
	int m_live{ 3 };

	nc::Scene m_scene;

	float m_frameTime;
	float m_spawnTimer{ 0 };

};

