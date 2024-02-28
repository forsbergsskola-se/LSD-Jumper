#include "Game.h"

#include "Application.h"

bool Game::Create(Application* mainApplication)
{
	application = mainApplication;

	player = new Player;
	if (!player->Create(mainApplication))
		return false;

	camera = { 0.0f, 0.0f,(float) application->GetWindow()->GetWidth(),(float) application->GetWindow()->GetHeight() };

	return true;
}

void Game::Destroy()
{
	player->Destroy();
	delete player;

	application = nullptr;
}

void Game::Update(const float deltaTime)
{
	if (application->GetInputHandler()->KeyPressed(SDL_SCANCODE_ESCAPE))
		application->Quit();



	player->Update(deltaTime);
}

void Game::Render(SDL_Renderer* renderer)
{
	player->Render(renderer, camera);
}