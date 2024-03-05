#include "Application.h"

bool Application::Create()
{
	libraryHandler = new LibraryHandler;
	if (!libraryHandler->Create())
		return false;

	window = new Window;
	if (!window->Create())
		return false;

	textureHandler = new TextureHandler;
	if (!textureHandler->Create(window->GetRenderer()))
		return false;

	fontHandler = new FontHandler;
	audioHandler = new AudioHandler;
	inputhandler = new InputHandler;

	game = new Game;
	if (!game->Create(this))
		return false;

	font = fontHandler->CreateFont("Assets/Fonts/RockwellNova-Light.ttf", 50);
	if (!font)
		return false;

	return true;
}

void Application::Destroy()
{
	fontHandler->DestroyFont(font);

	game->Destroy();
	delete game;

	delete inputhandler;
	delete audioHandler;
	delete fontHandler;

	textureHandler->Destroy();
	delete textureHandler;

	window->Destroy();
	delete window;

	libraryHandler->Destroy();
	delete libraryHandler;
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
	inputhandler->Update();
	timer.Update();

	switch (curState)
	{
		case Application::Menu:
		{
			// if start-game button is pressed
			//	curState = State::Play;	

			// If quit-button is pressed, application->Quit();

			if (inputhandler->KeyPressed(SDL_SCANCODE_1))
				curState = State::Play;

			break;
		}
		case Application::Play:
		{
			game->Update((float)timer.GetDeltaTime());

			// if player dies, curState = State::Dead;

			break; 
		}
		case Application::Dead:
		{
			// If Play-again button is pressed, curState = State::Play;
			// If Quit-game button is pressed, application->Quit();

			break; 
		}
		default:
			break;
	}
}

void Application::Render()
{
	window->BeginRender();
	
	switch (curState)
	{
		case Application::Menu:
		{
			window->RenderText(font, "Start Game", 300, 300, {255, 255, 255, 255});

			break;
		}
		case Application::Play:
		{
			game->Render(window->GetRenderer());

			break;
		}
		case Application::Dead:
		{


			break;
		}
		default:
			break;
	}
	
	window->EndRender();
}

