#include "Game.h"

#include "Application.h"

bool Game::Create(Application* mainApplication)
{
	application = mainApplication;

	player = new Player;
	if (!player->Create(mainApplication))
		return false;

	return true;
}

void Game::Destroy()
{
	player->Destroy(application);
	delete player;

	application = nullptr;
}

void Game::Update(const float deltaTime)
{
	player->Update(deltaTime);
}

void Game::Render(SDL_Renderer* renderer)
{
	player->Render(renderer);
}
