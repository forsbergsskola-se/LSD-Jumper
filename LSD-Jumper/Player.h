#pragma once

#include <SDL.h>

class Application;

class Player
{
public:

	Player();
	~Player();

	bool Create(Application* mainApplication);
	void Destroy();
	void Update(const float deltaTime);
	void Render(SDL_Renderer* renderer);

private:

	Application* application = nullptr;

	// Player texture
	SDL_Texture* texture = nullptr;

	//collider
	SDL_FRect rect = { 0.0f, 0.0f, 0.0f, 0.0f };

	// Player position
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float gravity = 100.0f;

};