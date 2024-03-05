#include "Player.h"
#include <iostream>
#include "Application.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Create(Application* mainApplication)
{
	application = mainApplication;

	texture = application->GetTextureHandler()->CreateTexture("Assets/Textures/character.png");
	if (!texture)
		return false;

	rect = { 0.0f, 0.0f, 115.0f * 0.7f, 185.0f * 0.7f };

	xPosition = application->GetWindow()->GetWidth() * 0.5f;
	yPosition = application->GetWindow()->GetHeight() - rect.h;

	rect.x = xPosition;
	rect.y = yPosition;

	jumpCount = 0;
	maxJumpCount = 2;

	return true;
}

void Player::Destroy()
{
	application->GetTextureHandler()->DestroyTexture(texture);
}

void Player::Update(const float deltaTime) {
    if (application->GetInputHandler()->KeyHeld(SDL_SCANCODE_LEFT)) 
    {
        xPosition -= 350.0f * deltaTime;
    }
    else if (application->GetInputHandler()->KeyHeld(SDL_SCANCODE_RIGHT)) 
    {
        xPosition += 350.0f * deltaTime;
    }

    if (application->GetInputHandler()->KeyPressed(SDL_SCANCODE_SPACE)) 
    {
        if (!jumping || (jumpCount < maxJumpCount)) 
        {
            jumping = true;
            yVelocity = -jumpSpeed;
            jumpCount++; 

            jumpSound = application->GetAudioHandler()->CreateAudio("Assets/Textures/jump.wav");
            if (!jumpSound)
            {
                std::cout << "Failed to load sound." << std::endl;
            }

            Mix_PlayChannel (-1, jumpSound, 0);
        }
    }

    if (jumping) {
        yVelocity += gravity * deltaTime;
        yPosition += yVelocity * deltaTime;
    }

    if ((yPosition > application->GetWindow()->GetHeight() - rect.h)) 
    {
        yPosition = application->GetWindow()->GetHeight() - rect.h;
        yVelocity = 0.0f; 
        jumping = false;
        jumpCount = 0; 
    }

    rect.x = xPosition;
    rect.y = yPosition;
}

void Player::Render(SDL_Renderer* renderer, SDL_FRect cameraRect)
{
	const SDL_FRect rectPlayer = { rect.x - cameraRect.x, rect.y - cameraRect.y, rect.w, rect.h };

	SDL_RenderCopyF(renderer, texture, nullptr, &rectPlayer);
}