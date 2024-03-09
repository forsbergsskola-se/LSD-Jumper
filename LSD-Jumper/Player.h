#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

class Application;

class Player
{
public:

	 Player() {}
	~Player() {}

	bool Create(Application* mainApplication);
	void Destroy();
	void HandleInput(const float deltaTime);
	void Update(const float deltaTime, const std::vector<SDL_FRect>& levelColliders);
	void Render(SDL_Renderer* renderer, const SDL_FRect& cameraRect);

public:

	// Getters/Setters

	SDL_FRect& GetCollider() {return collider;}		//making a getter instead of making a collider public

	float GetYPosition() {return yPosition;}
	float GetScore() {return highestScore;}

private:

	void SyncColliders();

private:

	Application* application = nullptr;

	SDL_Texture* texture = nullptr;

	Mix_Chunk* jumpSound = nullptr;

	SDL_FRect collider = {0.0f, 0.0f, 0.0f, 0.0f};

	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float gravity = 1500.0f;
	float xVelocity = 0.0f;
	float yVelocity = 0.0f;
	float movementSpeed = 350.0f;
	float jumpStrength = 700.0f;
	float score = 0.0f;
	float highestScore = 0.0f;

	int direction = 1; // 0 = facing left, 1 = facing right

	bool jumping = false;

};