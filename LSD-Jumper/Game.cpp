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

	camera = { 0.0f, 0.0f,(float)application->GetWindow()->GetWidth(),(float)application->GetWindow()->GetHeight() };

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

	if (application->GetInputHandler()->KeyHeld(SDL_SCANCODE_A))
		camera.y -= 100.0f * deltaTime;

	else if (application->GetInputHandler()->KeyHeld(SDL_SCANCODE_D))
		camera.y += 100.0f * deltaTime;

	player->Update(deltaTime);
	level->Update(deltaTime);
}

void Game::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, background, nullptr, nullptr);
	player->Render(renderer, camera);
	level->Render(renderer, camera);
}

