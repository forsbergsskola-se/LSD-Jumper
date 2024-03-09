#include "Application.h"

#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"

Application::Application()
{
	// Seed the random number generator
	srand(time(0));

	for(int i = 0; i < States::NUM_STATES; i++)
	{
		states[i] = nullptr;
	}
}

bool Application::Create()
{
	libraryHandler = new LibraryHandler;
	if (!libraryHandler->Create())
		return false;

	window = new Window;
	if (!window->Create())
		return false;

	defaultFont = fontHandler->CreateFont("Assets/Fonts/VT323-Regular.ttf", 50);
	if (!defaultFont)
		return false;

	textureHandler = new TextureHandler;
	if (!textureHandler->Create(window->GetRenderer()))
		return false;

	fontHandler = new FontHandler;
	audioHandler = new AudioHandler;
	inputHandler = new InputHandler;

	State* menuState = new MenuState;
	if(!menuState->Create(this))
		return false;

	State* gameState = new GameState;
	if(!gameState->Create(this))
		return false;

	State* gameOverState = new GameOverState;
	if(!gameOverState->Create(this))
		return false;

	states[States::MENU] = menuState;
	states[States::GAME] = gameState;
	states[States::GAME_OVER] = gameOverState;

	// Set the start state
	currentState = states[States::MENU];
	if(!currentState->OnEnter())
		return false;

	return true;
}

void Application::Destroy()
{
	if(currentState)
		currentState->OnExit();

	for(int i = 0; i < States::NUM_STATES; i++)
	{
		if(states[i])
		{
			states[i]->Destroy();
			delete states[i];
			states[i] = nullptr;
		}
	}

	delete inputHandler;
	delete audioHandler;
	delete fontHandler;
	inputHandler = nullptr;
	audioHandler = nullptr;
	fontHandler = nullptr;

	textureHandler->Destroy();
	delete textureHandler;
	textureHandler = nullptr;

	fontHandler->DestroyFont(defaultFont);
	defaultFont = nullptr;

	window->Destroy();
	delete window;
	window = nullptr;

	libraryHandler->Destroy();
	delete libraryHandler;
	libraryHandler = nullptr;
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
	inputHandler->Update();
	timer.Update();

	if(currentState)
		currentState->Update((float)timer.GetDeltaTime());

	// If there's a pending state
	if(nextState)
	{
		// Stop/exit the current state (see 'OnExit' function in each state) 
		if(currentState)
			currentState->OnExit();

		// Do the state change
		currentState = nextState;

		// And start/enter the new state (see 'OnEnter' function in each state) 
		if(!currentState->OnEnter())
			running = false;

		nextState = nullptr;
	}
}

void Application::Render()
{
	window->BeginRender();

	if(currentState)
		currentState->Render();
	
	window->EndRender();
}

bool Application::SetState(const int newState)
{
	nextState = states[newState];

	return true;
}

void Application::EndRound(const int score)
{
	highestScore = score;

	SetState(States::GAME_OVER);
}