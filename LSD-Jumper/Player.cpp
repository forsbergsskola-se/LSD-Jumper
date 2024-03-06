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

	int playerWidth = 0;
	int playerHeight = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &playerWidth, &playerHeight);

	collider = {0.0f, 0.0f, (float)(playerWidth * 0.7f), (float)(playerHeight * 0.7f)};

	xPosition = application->GetWindow()->GetWidth() * 0.5f;
	yPosition = application->GetWindow()->GetHeight() - collider.h;

	collider.x = xPosition;
	collider.y = yPosition;

	return true;
}

void Player::Destroy()
{
	application->GetTextureHandler()->DestroyTexture(texture);
	application->GetAudioHandler()->DestroyAudio(jumpSound);
}

void Player::HandleInput(const float deltaTime)
{
	xVelocity = 0.0f;

	if(application->GetInputHandler()->KeyHeld(SDL_SCANCODE_LEFT))
	{
		xVelocity = -movementSpeed;

		direction = 0;
	}

	else if(application->GetInputHandler()->KeyHeld(SDL_SCANCODE_RIGHT))
	{
		xVelocity = movementSpeed;

		direction = 1;
	}

	if(application->GetInputHandler()->KeyPressed(SDL_SCANCODE_SPACE) && !jumping)
	{
		Mix_PlayChannel(-1, jumpSound, 0);
		yVelocity = -jumpStrength;
		jumping = true;
	}
}

void Player::Update(const float deltaTime, const std::vector<SDL_FRect>& levelColliders)
{
	HandleInput(deltaTime);

	const float windowWidth = (float)application->GetWindow()->GetWidth();
	const float windowHeight = (float)application->GetWindow()->GetHeight();

	xPosition += xVelocity * deltaTime;
	yVelocity += gravity * deltaTime;
	yPosition += yVelocity * deltaTime;

	// Make sure that the player can't leave the window's left- and right edges
		 if (xPosition < 0.0f)						xPosition = 0.0f;
	else if (xPosition > windowWidth - collider.w)	xPosition = windowWidth - collider.w;

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

	score = (float)application->GetWindow()->GetHeight() - yPosition - collider.h;
}

void Player::Render(SDL_Renderer* renderer, const SDL_FRect& cameraRect)
{
	const SDL_FRect playerRectWorld = {collider.x - cameraRect.x, collider.y - cameraRect.y, collider.w, collider.h};

	// Only for debugging
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderDrawRectF(renderer, &playerRectWorld);

	SDL_RenderCopyExF(renderer, texture, nullptr, &playerRectWorld, 0.0f, nullptr, ((direction == 1) ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL));

	const std::string text = "Score: " + std::to_string((int)score);

	application->GetWindow()->RenderText(application->GetFont(), text, 5.0f, 5.0f, { 0, 0, 0, 255 });
}

void Player::SyncColliders()
{
	collider.x = xPosition;
	collider.y = yPosition;
}