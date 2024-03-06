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

	const float windowWidth = (float)window->GetWidth() * 0.5f;
	const float windowHeight = (float)window->GetHeight() * 0.5f;
	const SDL_Color buttonBackgroundColor = { 100, 100, 100, 255 };
	const SDL_Color buttonTextColor = { 255, 255, 255, 255 };
	const SDL_Color buttonTextHoveredColor = { 255, 0, 0, 255 };

	startGameButton.Create(window->GetRenderer(), font, "Start Game", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	startGameButton.SetPosition(windowWidth - (startGameButton.GetWidth() * 0.5f), windowHeight - (startGameButton.GetWidth() * 0.5f) - 30.0f);
	quitButton.Create(window->GetRenderer(), font, "Quit", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	quitButton.SetPosition(windowWidth - (quitButton.GetWidth() * 0.5f), windowHeight - (quitButton.GetWidth() * 0.5f) + 30.0f);
	restartGameButton.Create(window->GetRenderer(), font, "Restart", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	restartGameButton.SetPosition(windowWidth - (restartGameButton.GetWidth() * 0.5f), windowHeight - (restartGameButton.GetWidth() * 0.5f) + 0.0f);

	return true;
}

void Application::Destroy()
{
	restartGameButton.Destroy();
	quitButton.Destroy();
	startGameButton.Destroy();

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
			if (quitButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
				running = false;

			if (startGameButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
				curState = State::Play;

			break;
		}

		case Application::Play:
		{
			game->Update((float)timer.GetDeltaTime());

			

			break; 
		}

		case Application::Dead:
		{
			// If Play-again button is pressed, curState = State::Play;
			if (restartGameButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
			curState = State::Play;

			// If Quit-game button is pressed, application->Quit();
			if (quitButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
				running = false;

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
			quitButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());
			startGameButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());

			break;
		}

		case Application::Play:
		{
			game->Render(window->GetRenderer());

			break;
		}

		case Application::Dead:
		{
			restartGameButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());
			quitButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());

			break;
		}

		default:
			break;
	}
	
	window->EndRender();
}
