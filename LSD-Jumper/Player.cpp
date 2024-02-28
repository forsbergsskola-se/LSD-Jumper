#include "Player.h"

#include "Application.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Create(Application* application)
{
	texture = application->GetTextureHandler()->CreateTexture("Assets/Textures/character.png");
	if (!texture)
		return false;

	rect = { 0.0f, 0.0f, 115.0f * 0.7f, 185.0f * 0.7f };

	return true;
}

void Player::Destroy(Application* application)
{
	application->GetTextureHandler()->DestroyTexture(texture);
}

void Player::Update(const float deltaTime)
{

}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, texture, nullptr, &rect);
}