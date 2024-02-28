#include "Game.h"

#include "Application.h"

bool Game::Create(Application* mainApplication)
{
	application = mainApplication;

	background = application->GetTextureHandler()->CreateTexture("Assets/Textures/background.png");
	if (!background)
		return false;

	level = new Level;
	if (!level->Create(mainApplication))
		return false;

	player = new Player;
	if (!player->Create(mainApplication))
		return false;

	return true;
}

void Game::Destroy()
{
	player->Destroy();
	delete player;

	level->Destroy();
	delete level;

	application->GetTextureHandler()->DestroyTexture(background);

	application = nullptr;
}

void Game::Update(const float deltaTime)
{
	if (application->GetInputHandler()->KeyPressed(SDL_SCANCODE_ESCAPE))
		application->Quit();

	player->Update(deltaTime);
	level->Update(deltaTime);
}

void Game::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, background, nullptr, nullptr);
	player->Render(renderer);
	level->Render(renderer);
}