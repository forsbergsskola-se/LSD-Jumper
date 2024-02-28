#include "Game.h"

#include "Application.h"

bool Game::Create(Application* mainApplication)
{
	application = mainApplication;

	texture = application->GetTextureHandler()->CreateTexture("Assets/Textures/smiley.png");

	return true;
}

void Game::Destroy()
{
	application->GetTextureHandler()->DestroyTexture(texture);
	application = nullptr;
}

void Game::Update(const float deltaTime)
{

}

void Game::Render(SDL_Renderer* renderer)
{
	//SDL_SetRenderDrawColor(renderer, 255,0,0,255);
	//SDL_RenderFillRect(renderer, &rect);
	//SDL_Rect rect = { 200,200,200,200 };

//	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}
