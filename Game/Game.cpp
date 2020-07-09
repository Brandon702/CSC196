/*
NOTE:
Loading directory doesnt work, it looks for C:\Build instead of $(SolutionDir)Build
*/

#include "core.h"
#include "Math\Math.h"
#include "Math\Random.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <string>

//std::vector<nc::Vector2> points = { { 0, -5 }, { 4, 2 }, {0,5}, {-4,2}, {0,-5} };
//nc::Color color{ 0.7,0.7,1 };
nc::Shape ship;
nc::Transform transform{ { 400, 300 }, 5, 0 };

nc::Vector2 position{ 960.0f ,540.0f };
float speed = 300.0f;
float scale = 3.0f;
float angle = 0.0f;

float frameTime;
DWORD prevTime;
DWORD deltaTime;
float roundTime{ 0 };
bool gameOver = { false };

bool Update(float dt) //dt = (1/60) = 0.1667 | (1/90) = 0.0111
{
	frameTime = dt;
	roundTime += dt;
	if (roundTime >= 15) gameOver = true;

	if (gameOver) dt = 0;
	//Get delta time
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	int x, y;
	Core::Input::GetMousePos(x,y);

	//nc::Vector2 target = nc::Vector2{ x,y };
	//nc::Vector2 direction = target - position;

	//direction.Normalize();

	//if (direction.Length() < 50.0f)
	{
		//position = position + (direction * speed);
	}

	//position = position + direction * 0.05;

	//position = nc::Vector2{ x,y };

	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed; }
	nc::Vector2 direction = force * dt;
	direction = nc::Vector2::Rotate(direction, angle);
	//position = position + direction;

	transform.position = transform.position + direction;

	if (transform.position.x > 1920) transform.position.x = 1920;
	if (transform.position.x < 0) transform.position.x = 0;
	if (transform.position.y > 1080) transform.position.y = 1080;
	if (transform.position.y < 0) transform.position.y = 0;

	//if (Core::Input::IsPressed('A')) position += nc::Vector2::left * (speed * dt);
	//if (Core::Input::IsPressed('D')) position += nc::Vector2::right * (speed * dt);
	if (Core::Input::IsPressed('W')) transform.position += nc::Vector2::up *(speed * dt);
	//if (Core::Input::IsPressed('S')) position += nc::Vector2::down *(speed * dt);
	if (Core::Input::IsPressed('Q')) transform.angle -= dt * 3;
	if (Core::Input::IsPressed('E')) transform.angle += dt * 3;
	//for (nc::Vector2& point : points)
	//{
	//	point = nc::Vector2{ nc::random(-10.0f,10.0f), nc::random(-10.0f,10.0f) };
	//}

	//for (size_t i = 0; i < NUM_POINTS; i++)
	//{
	//	points[i] = nc::Vector2{ nc::random(0.0f, 1920.0f), nc::random(0.0f, 1080.0f) };
	//}
	//return false;
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1, 1, 1 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 25, std::to_string(1.0f/frameTime).c_str());
	graphics.DrawString(10, 40, std::to_string(deltaTime/1000.f).c_str());
	if (gameOver) graphics.DrawString(1920/2, 1080/2, "Game Over");

	//graphics.SetColor(m_color);
	ship.Draw(graphics, position, scale, angle);
	//graphics.DrawLine(nc::random(0.0f,1920.0f), nc::random(0.0f, 1080.0f), nc::random(0.0f, 1920.0f), nc::random(0.0f, 1080.0f));

	
}

int main()
{
	DWORD time = GetTickCount();
	std::cout << time / 1000 / 60 / 60 / 24 << std::endl;

	ship.Load("ship.txt");
	//ship.SetColor(nc::Color{1,1,1});

	char name[] = "CSC196";
	Core::Init(name, 1920, 1080, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
