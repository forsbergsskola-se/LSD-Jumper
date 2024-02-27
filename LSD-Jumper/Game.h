#pragma once
#include <SDL.h>

class Game
{
public:

	Game() {};
	~Game() {};
	bool Create();
	void Destroy();
	void Update(const float deltaTime);
	void Render(SDL_Renderer* renderer);
private:

};

