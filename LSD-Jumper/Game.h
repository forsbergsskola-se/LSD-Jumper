#pragma once

#include "Player.h"

#include <SDL.h>

//forward declaring application, avoid multiple includes
class Application;

class Game
{
public:

	Game() {};
	~Game() {};
	bool Create(Application* mainApplication);
	void Destroy();
	void Update(const float deltaTime);
	void Render(SDL_Renderer* renderer);

private:

	Application* application = nullptr;

	Player* player = nullptr;

	SDL_FRect camera = {0.0f, 0.0f, 0.0f, 0.0f};

};

