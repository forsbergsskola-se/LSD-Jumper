#include "Application.h"

bool Application::Create()
{
	/* TRYING TO PUT IN THE BACKGROUND FOR THE DEAD STATE
	gameOver = GetTextureHandler()->CreateTexture("Assets/Textures/background.png");
	std::cout << "Texture created!" << std::endl;
	if (!gameOver)
	{
		std::cout << "Failed to load gameOver texture." << std::endl;
		return false;
	}
	*/

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

	myMusic = audioHandler->CreateMusic("Assets/Audio/ghost.wav");
	if (!myMusic)
	{
		std::cout << "Failed to load music." << std::endl;
		return false;
	}

	//BACKGROUND MUSIC
	//Mix_PlayMusic(myMusic, -1);

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
	restartGameButton.SetPosition(windowWidth - (restartGameButton.GetWidth() * 0.5f), windowHeight - (restartGameButton.GetWidth() * 0.5f) - 275.0f);

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

	//GameOver Texture
	GetTextureHandler()->DestroyTexture(gameOver);
	std::cout << "Game over texture destroyed." << std::endl;

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
			game->Update((float)timer.GetDeltaTime());
			if (restartGameButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
			{
				curState = State::Menu;
				game->Destroy();
				delete game;

				game = new Game;
				if (!game->Create(this))
				{
					std::cout << "Failed to create game." << std::endl;
					return;
				}

				Render();
			}
			break;

		case Application::Dead:
		{
			// If Play-again button is pressed, curState = State::Menu;
			if (restartGameButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
			{
				curState = State::Menu;
				game->Destroy();
				delete game;

				game = new Game;
				if (!game->Create(this))
				{
					std::cout << "Failed to create game." << std::endl;
					return;
				}

				Render();
			}


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
			restartGameButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());

			break;
		}

		case Application::Dead:
		{
			//Render the background GAME OVER
			SDL_RenderCopyF(renderGameOver, gameOver, nullptr, nullptr);

			quitButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());
			restartGameButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());

			const std::string highestScoreText = "Highest Score: " + std::to_string((int)highestScore);
			GetWindow()->RenderText(GetFont(), highestScoreText, (GetWindow()->GetWidth() * 0.33f), (GetWindow()->GetHeight() * 0.6f), { 0, 0, 0, 255 });


			break;
		}

		default:
			break;
	}
	
	window->EndRender();
}
void Application::UpdateHighestScore(float score)
{
	if (score > highestScore)
	{
		highestScore = score;
	}
}
