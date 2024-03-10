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

	gameOver = GetTextureHandler()->CreateTexture("Assets/Textures/gameover.png");
	if (!gameOver)
	{
		std::cout << "Failed to load gameOver texture." << std::endl;
		return false;
	}
	start = GetTextureHandler()->CreateTexture("Assets/Textures/menu.png");
	if (!start)
	{
		std::cout << "Failed to load gameOver texture." << std::endl;
		return false;
	}

	fontHandler = new FontHandler;
	audioHandler = new AudioHandler;
	inputhandler = new InputHandler;

	menuMusic = audioHandler->CreateMusic("Assets/Audio/menu.mp3");
	if (!menuMusic)
	{
		std::cout << "Failed to load music." << std::endl;
		return false;
	}

	gameMusic = audioHandler->CreateMusic("Assets/Audio/game.mp3");
	if (!gameMusic)
	{
		std::cout << "Failed to load music." << std::endl;
		return false;
	}

	gameOverMusic = audioHandler->CreateMusic("Assets/Audio/gameover.mp3");
	if (!gameOverMusic)
	{
		std::cout << "Failed to load game over music." << Mix_GetError() << std::endl;
		return false;
	}

	//BACKGROUND MUSIC
	//Mix_PlayMusic(menuMusic, -1);
	//Mix_PlayMusic(gameMusic, -1);
	//Mix_PlayMusic(gameOverMusic, -1);

	game = new Game;
	if (!game->Create(this))
		return false;

	font = fontHandler->CreateFont("Assets/Fonts/VT323-Regular.ttf", 50);
	if (!font)
		return false;

	nameFont = fontHandler->CreateFont("Assets/Fonts/VT323-Regular.ttf", 100);
	if (!nameFont)
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

	fontHandler->DestroyFont(nameFont);
	fontHandler->DestroyFont(font);

	game->Destroy();
	delete game;

	delete inputhandler;
	delete audioHandler;
	delete fontHandler;

	GetTextureHandler()->DestroyTexture(start);
	GetTextureHandler()->DestroyTexture(gameOver);

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
		// Check if menu music is playing, if not... start playing it
		if (!Mix_PlayingMusic())
		{
			Mix_HaltMusic();
			Mix_PlayMusic(menuMusic, -1);
		}

		if (quitButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
			running = false;

		if (startGameButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
		{
			curState = State::Play;
			// Halt menu music and start playing game music
			Mix_HaltMusic();
			Mix_PlayMusic(gameMusic, -1);
		}

		break;
	}


		case Application::Play:
			game->Update((float)timer.GetDeltaTime());

			if (!Mix_PlayingMusic())
			{
				Mix_HaltMusic();
				Mix_PlayMusic(gameMusic, -1);
			}

			
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

				Mix_HaltMusic();
				Mix_PlayMusic(menuMusic, -1);

				Render();
			}
			break;

		case Application::Dead:
		{
			//std::cout << "In Dead state!" << std::endl;

			if (!gameOverMusicPlaying)	//IT WORKS!!
			{
				if (Mix_PlayingMusic() == 1)
				{
					Mix_HaltMusic();
					std::cout << "Music halted." << std::endl;
				}

				Mix_PlayMusic(gameOverMusic, -1);
				std::cout << "Playing gameOverMusic." << std::endl;

				gameOverMusicPlaying = true;
			}

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
				Mix_HaltMusic();
				Mix_PlayMusic(menuMusic, -1);

				Render();
			}

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
			SDL_RenderCopyF(window->GetRenderer(), start, nullptr, nullptr);

			quitButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());
			startGameButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());

			const std::string highestScoreText = "Highest Score: " + std::to_string((int)highestScore);
			GetWindow()->RenderText(GetFont(), highestScoreText, (GetWindow()->GetWidth() * 0.37f), (GetWindow()->GetHeight() * 0.6f), { 0, 0, 0, 255 });
			
			
			const std::string gameName = "LSD-JUMPER";
			SDL_Color nameColor = { 0, 255, 255, 255 }; // color not working
			GetWindow()->RenderText(GetNameFont(), gameName, (GetWindow()->GetWidth() * 0.35f), (GetWindow()->GetHeight() * 0.1f), nameColor);
			

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
			SDL_RenderCopyF(window->GetRenderer(), gameOver, nullptr, nullptr);

			quitButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());
			restartGameButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());

			const std::string highestScoreText = "Highest Score: " + std::to_string((int)highestScore);
			GetWindow()->RenderText(GetFont(), highestScoreText, (GetWindow()->GetWidth() * 0.35f), (GetWindow()->GetHeight() * 0.6f), { 0, 0, 0, 255 });


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
