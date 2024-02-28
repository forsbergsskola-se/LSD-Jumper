#include "Game.h"

#include "Application.h"

bool Game::Create(Application* mainApplication)
{
	application = mainApplication;

	background = application->GetTextureHandler()->CreateTexture("Assets/Textures/background.png");
	if (!background)
		return false;

	player = new Player;
	if (!player->Create(mainApplication))
		return false;

	level = new Level;
	level->Create(application);
	if (!level->Create(application))
		return false;


	return true;
}

void Game::Destroy()
{

	level->Destroy();
	delete level;

	player->Destroy(application);
	delete player;

	application->GetTextureHandler()->DestroyTexture(background);

	application = nullptr;
}

void Game::Update(const float deltaTime)
{
	level->Update(deltaTime);
	player->Update(deltaTime);
}

void Game::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, background, nullptr, nullptr);
	player->Render(renderer);
	level->Render(renderer);
}
