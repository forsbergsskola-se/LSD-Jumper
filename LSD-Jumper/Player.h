#pragma once

#include <SDL.h>

class Application;

class Player
{
public:

	Player();
	~Player();

	bool Create(Application* application);
	void Destroy(Application* application);
	void Update(const float deltaTime);
	void Render(SDL_Renderer* renderer);

private:

	SDL_Texture* texture = nullptr;

};