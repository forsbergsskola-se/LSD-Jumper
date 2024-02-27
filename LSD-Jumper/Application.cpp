#include "Application.h"

Application::Application()
{

}

Application::~Application()
 {

 }

bool Application::Create()
{
	libraryHandler = new LibraryHandler;
	if (!libraryHandler->Create())
		return false;

	window = new Window;
	if (!window->Create())
		return false;

	game = new Game;
	if (!game->Create())
		return false;

	return true;
}

void Application::Destroy()
{
	window->Destroy();
	delete window;

	libraryHandler->Destroy();
	delete libraryHandler;

	game->Destroy();
	delete game;
}

void Application::Run() 
{
	while (running)
	{
		HandleEvents();
		Update();
		Render();
	}
}

void Application::HandleEvents()
{
	SDL_Event event = {};
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				running = false;

				break;
			}

			default:
				break;
		}
	}
}

void Application::Update()
{
	timer.Update();
	game->Update((float)timer.GetDeltaTime());
}

void Application::Render()
{
	window->BeginRender();
	game->Render(window->GetRenderer());
	window->EndRender();
}

