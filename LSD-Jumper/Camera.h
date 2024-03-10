#pragma once

#include <SDL.h>

class Player;

class Camera
{
public:

	 Camera(void) {}
	~Camera(void) {}

	void Create(const float windowWidth, const float windowHeight);
	void Update(Player* player, const float deltaTime);

	SDL_FRect& GetRect() {return cameraRect;}

private:

	SDL_FRect cameraRect = {0.0f, 0.0f, 0.0f, 0.0f};

	float yPosition = 0.0f;
	float fraction = 0.0f;
	float easeFactor = 2.0f;

};