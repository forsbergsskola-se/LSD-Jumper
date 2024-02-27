#include "Game.h"

bool Game::Create()
{
	return true;
}

void Game::Destroy()
{

}

void Game::Update(const float deltaTime)
{

}

void Game::Render(SDL_Renderer* renderer)
{
	SDL_Rect rect = { 200,200,200,200 };
	SDL_SetRenderDrawColor(renderer, 255,0,0,255);
	SDL_RenderFillRect(renderer, &rect);
}
