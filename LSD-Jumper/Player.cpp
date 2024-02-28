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
	texture = application->GetTextureHandler()->CreateTexture("Assets/Textures/smiley.png");
	if (!texture)
		return false;

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
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}
