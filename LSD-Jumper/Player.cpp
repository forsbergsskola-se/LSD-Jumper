#include "Player.h"

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

	return true;
}

void Player::Destroy()
{
	application->GetTextureHandler()->DestroyTexture(texture);
}

void Player::Update(const float deltaTime)
{
	if (application->GetInputHandler()->KeyHeld(SDL_SCANCODE_LEFT))
	{
		xPosition -= 200.0f * deltaTime;
	}

	else if (application->GetInputHandler()->KeyHeld(SDL_SCANCODE_RIGHT))
	{
		xPosition += 200.0f * deltaTime;
	}

	
	rect.x = xPosition;
	rect.y = yPosition;
}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, texture, nullptr, &rect);
}