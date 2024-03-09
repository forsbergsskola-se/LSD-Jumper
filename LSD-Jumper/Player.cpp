#include "Player.h"
#include <iostream>
#include "Application.h"

bool Player::Create(Application* mainApplication)
{
	application = mainApplication;

	jumpSound = application->GetAudioHandler()->CreateAudio("Assets/Audio/jump.wav");

	texture = application->GetTextureHandler()->CreateTexture("Assets/Textures/character.png");
	if(!texture)
		return false;

	Window* window = application->GetWindow();		//creating the shortcut instead of writing application->GetWindow()-> ...

	int playerWidth = 0;
	int playerHeight = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &playerWidth, &playerHeight);

	collider.w = (float)(playerWidth * 0.7f);		//instead of asigning to the collider we asign each W and H to the collider separately
	collider.h = (float)(playerHeight * 0.7f);

	xPosition = window->GetWidth() * 0.5f;
	yPosition = window->GetHeight() - collider.h;

	SyncColliders();

	return true;
}

void Player::Destroy()
{
	application->GetTextureHandler()->DestroyTexture(texture);
	application->GetAudioHandler()->DestroyAudio(jumpSound);
}

void Player::HandleInput(const float deltaTime)
{
	InputHandler* inputHandler = application->GetInputHandler();		//creating the shortcut

	if(inputHandler->KeyHeld(SDL_SCANCODE_LEFT))
	{
		xVelocity -= movementSpeed * deltaTime;
		direction = 0;
	}

	else if(inputHandler->KeyHeld(SDL_SCANCODE_RIGHT))
	{
		xVelocity += movementSpeed * deltaTime;
		direction = 1;
	}

	xPosition += xVelocity * deltaTime;

	if(/*inputHandler->KeyPressed(SDL_SCANCODE_SPACE) &&*/ !jumping)		//always jumping
	{
		Mix_PlayChannel(-1, jumpSound, 0);
		yVelocity = -jumpStrength;
		jumping = true;
	}
}


void Player::Update(const float deltaTime, const std::vector<SDL_FRect>& levelColliders)
{
	HandleInput(deltaTime);

	Window* window = application->GetWindow();		//another window shortcut
	const float windowWidth = (float)window->GetWidth();
	const float windowHeight = (float)window->GetHeight();

	xPosition += xVelocity * deltaTime;
	yVelocity += gravity * deltaTime;
	yPosition += yVelocity * deltaTime;

	// Make sure that the player can't leave the window's left- and right edges
	if (xPosition < 0.0f) 
		xPosition = 0.0f;
	else if (xPosition > windowWidth - collider.w) 
		xPosition = windowWidth - collider.w;

	if(yPosition > (windowHeight - collider.h))
	{
		yPosition = windowHeight - collider.h;
		yVelocity = 0.0f;
		jumping = false;
	}

	SyncColliders();

	// Only doing collision checking when the player is falling
	if(yVelocity > 0.0f)
	{
		for (int i = 0; i < (int)levelColliders.size(); i++)
		{
			const SDL_FRect levelCollider = levelColliders[i];

			// The current level collider is above the player's bottom part so just continue without checking collision against it
			if((levelCollider.y + levelCollider.h) < (yPosition + collider.h))
				continue;

			SDL_FRect intersection = {0.0f, 0.0f, 0.0f, 0.0f};
			if(SDL_IntersectFRect(&collider, &levelCollider, &intersection) == SDL_TRUE)
			{

				// Stop the player on top of the current platform
				yPosition -= intersection.h;
				yVelocity = 0.0f;
				jumping = false;

				SyncColliders();

				break;
			}
		}
	}

	score = (float)windowHeight - yPosition - collider.h;

	if (score > highestScore)
		highestScore = score;
}

void Player::Render(SDL_Renderer* renderer, const SDL_FRect& cameraRect)
{
	const SDL_FRect playerRectWorld = {collider.x - cameraRect.x, collider.y - cameraRect.y, collider.w, collider.h};
	SDL_RenderCopyExF(renderer, texture, nullptr, &playerRectWorld, 0.0f, nullptr, ((direction == 1) ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL));
}

void Player::SyncColliders()
{
	collider.x = xPosition;
	collider.y = yPosition;
}