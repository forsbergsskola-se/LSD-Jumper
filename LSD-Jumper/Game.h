#pragma once

#include "Player.h"
#include "Level.h"
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
	Level* level = nullptr;
	SDL_Texture* background = nullptr;
	Player* player = nullptr;

};

