#include "MenuState.h"

#include "Application.h"
#include "InputHandler.h"

bool MenuState::Create(Application* mainApplication)
{
	std::cout << "Creating menu state" << std::endl;

	// Create objects that should created once and should persist during the lifetime of the game

	application = mainApplication;

	return true;
}

void MenuState::Destroy()
{
	std::cout << "Destroying menu state" << std::endl;

	// Destroy objects that has been created once and should be destroyed in the end of the game's lifetime

	application = nullptr;
}

bool MenuState::OnEnter()
{
	std::cout << "Entering menu state" << std::endl;

	// Create objects that should be created/started when this state is entered/started (create textures, load/start menu music, load sounds etc)

	backgroundTexture = application->GetTextureHandler()->CreateTexture("Assets/Textures/menu.png");
	if (!backgroundTexture)
		return false;

	cloudTexture = application->GetTextureHandler()->CreateTexture("Assets/Textures/cloud.png");
	if (!cloudTexture)
		return false;
	SDL_SetTextureBlendMode(cloudTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(cloudTexture, 100);

	SpawnClouds();

	music = application->GetAudioHandler()->CreateMusic("Assets/Audio/menu.mp3");
	if (!music)
		return false;
	Mix_PlayMusic(music, -1);

	Window* window = application->GetWindow();
	SDL_Renderer* renderer = window->GetRenderer();
	TTF_Font* defaultFont = application->GetDefaultFont();
	const float windowWidth = (float)window->GetWidth() * 0.5f;
	const float windowHeight = (float)window->GetHeight() * 0.5f;
	const SDL_Color buttonBackgroundColor = { 100, 100, 100, 255 };
	const SDL_Color buttonTextColor = { 255, 255, 255, 255 };
	const SDL_Color buttonTextHoveredColor = { 255, 0, 0, 255 };

	LSDJumperTextBox.Create(renderer, defaultFont, "LSD Jumper", {0, 0, 0, 0}, buttonBackgroundColor, buttonBackgroundColor);
	LSDJumperTextBox.SetPosition(windowWidth - (LSDJumperTextBox.GetWidth() * 0.5f), windowHeight - (LSDJumperTextBox.GetHeight() * 0.5f) - 50.0f);
	startGameButton.Create(renderer, defaultFont, "Start Game", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	startGameButton.SetPosition(windowWidth - (startGameButton.GetWidth() * 0.5f), windowHeight - (startGameButton.GetHeight() * 0.5f) + 80.0f);
	quitButton.Create(renderer, defaultFont, "Quit", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	quitButton.SetPosition(windowWidth - (quitButton.GetWidth() * 0.5f), windowHeight - (quitButton.GetHeight() * 0.5f) + 150.0f);

	lifeTime = 0.0f;
	backgroundOffset = 0.0f;

	return true;
}

void MenuState::OnExit()
{
	std::cout << "Exiting menu state" << std::endl;

	// Destroy objects that should be destroyed/stopped when this state is exited/stopped (destroy textures, unload/stop menu music, unload sounds etc)

	clouds.clear();

	Mix_HaltMusic();
	application->GetAudioHandler()->DestroyMusic(music);
	music = nullptr;

	quitButton.Destroy();
	startGameButton.Destroy();
	LSDJumperTextBox.Destroy();

	application->GetTextureHandler()->DestroyTexture(backgroundTexture);
	backgroundTexture = nullptr;
}

void MenuState::Update(const float deltaTime)
{
	InputHandler* inputHandler = application->GetInputHandler();

	if (startGameButton.PointInside(inputHandler->GetMouseXPosition(), inputHandler->GetMouseYPosition()) && inputHandler->MouseButtonPressed(SDL_BUTTON_LEFT))
		application->SetState(Application::EState::GAME);

	if (quitButton.PointInside(inputHandler->GetMouseXPosition(), inputHandler->GetMouseYPosition()) && inputHandler->MouseButtonPressed(SDL_BUTTON_LEFT))
		application->Quit();

	const int windowWidth = application->GetWindow()->GetWidth();
	const int windowHeight = application->GetWindow()->GetHeight();

	lifeTime += deltaTime;
	backgroundOffset += 20.0f * deltaTime;

	if(backgroundOffset > (float)windowWidth)
		backgroundOffset = 0.0f;

	for(int i = 0; i < (int)clouds.size(); ++i)
	{
		SDL_FRect& cloudRect = clouds[i].rect;

		cloudRect.y += clouds[i].speed * deltaTime;

		if (cloudRect.y > windowHeight)
		{
			const int minX = 0;
			const int maxX = windowWidth - (int)(cloudRect.x * 0.5f);
			const int minY = (int)-(cloudRect.h + 50);
			const int maxY = (int)-(cloudRect.h + 30);
			const float xPosition = (float)(rand() % (maxX - minX) + minX);
			const float yPosition = (float)(rand() % (maxY - minY) + minY);

			cloudRect.x = xPosition;
			cloudRect.y = yPosition;
		}
	}
}

void MenuState::Render()
{
	SDL_Renderer* renderer = application->GetWindow()->GetRenderer();
	InputHandler* inputHandler = application->GetInputHandler();
	const float mouseXPosition = inputHandler->GetMouseXPosition();
	const float mouseYPosition = inputHandler->GetMouseYPosition();

	const float sin = (sinf(lifeTime * 1.0f) + 1.0f) * 0.5f;
	const float cos = (cosf(lifeTime * 1.0f) + 1.0f) * 0.5f;
	const Uint8 r = 255 - (Uint8)(sin * 50.0f);
	const Uint8 g = 255 - (Uint8)(cos * 50.0f);
	const Uint8 b = 255 - (Uint8)(sin * 50.0f);
	Uint8 textureCurrentRMod = 0;
	Uint8 textureCurrentGMod = 0;
	Uint8 textureCurrentBMod = 0;
	SDL_GetTextureColorMod(backgroundTexture, &textureCurrentRMod, &textureCurrentGMod, &textureCurrentBMod);
	SDL_SetTextureColorMod(backgroundTexture, r, g, b);

	int textureWidth = 0;
	int textureHeight = 0;
	SDL_QueryTexture(backgroundTexture, nullptr, nullptr, &textureWidth, &textureHeight);

	for(int i = 0; i < 2; ++i)
	{
		const SDL_FRect dstRect = {(textureWidth * i) - backgroundOffset, 0, (float)textureWidth, (float)textureHeight};
		SDL_RenderCopyF(renderer, backgroundTexture, nullptr, &dstRect);
	}


	for(int i = 0; i < (int)clouds.size(); ++i)
	{
		SDL_SetTextureAlphaMod(cloudTexture, clouds[i].alpha);
		SDL_RenderCopyF(renderer, cloudTexture, nullptr, &clouds[i].rect);
	}

	LSDJumperTextBox.Render(renderer, 0.0f, 0.0f);
	startGameButton.Render(renderer, mouseXPosition, mouseYPosition);
	quitButton.Render(renderer, mouseXPosition, mouseYPosition);
}

void MenuState::SpawnClouds()
{
	const int windowWidth = application->GetWindow()->GetWidth();
	int cloudWidth = 0;
	int cloudHeight = 0;
	SDL_QueryTexture(cloudTexture, nullptr, nullptr, &cloudWidth, &cloudHeight);

	for(int i = 0; i < 25; ++i)
	{
		const float scale = 0.10f;
		const int cloudWidthScaled = (int)(cloudWidth * scale);
		const int cloudHeightScaled = (int)(cloudHeight * scale);
		const int minX = 0;
		const int maxX = windowWidth - (int)(cloudWidthScaled * 0.5f);
		const int minY = -(cloudHeightScaled + 10);
		const int maxY = -(cloudHeightScaled + 20);
		const int speedMin = 5;
		const int speedMax = 15;
		const float xPosition = (float)(rand() % (maxX - minX) + minX);
		const float yPosition = (float)(rand() % (maxY - minY) + minY);
		const float speed = (float)(rand() % (speedMax - speedMin) + speedMin);

		SCloudData cloudData = {{xPosition, yPosition, (float)cloudWidthScaled, (float)cloudHeightScaled}, speed, 70};
		clouds.push_back(cloudData);
	}

	for(int i = 0; i < 25; ++i)
	{
		const float scale = 0.20f;
		const int cloudWidthScaled = (int)(cloudWidth * scale);
		const int cloudHeightScaled = (int)(cloudHeight * scale);
		const int minX = 0;
		const int maxX = windowWidth - (int)(cloudWidthScaled * 0.5f);
		const int minY = -(cloudHeightScaled + 50);
		const int maxY = -(cloudHeightScaled + 30);
		const int speedMin = 20;
		const int speedMax = 40;
		const float xPosition = (float)(rand() % (maxX - minX) + minX);
		const float yPosition = (float)(rand() % (maxY - minY) + minY);
		const float speed = (float)(rand() % (speedMax - speedMin) + speedMin);

		SCloudData cloudData = {{xPosition, yPosition, (float)cloudWidthScaled, (float)cloudHeightScaled}, speed, 100};
		clouds.push_back(cloudData);
	}

	for(int i = 0; i < 10; ++i)
	{
		const float scale = 0.60f;
		const int cloudWidthScaled = (int)(cloudWidth * scale);
		const int cloudHeightScaled = (int)(cloudHeight * scale);
		const int minX = 0;
		const int maxX = windowWidth - (int)(cloudWidthScaled * 0.5f);
		const int minY = -(cloudHeightScaled + 50);
		const int maxY = -(cloudHeightScaled + 30);
		const int speedMin = 40;
		const int speedMax = 70;
		const float xPosition = (float)(rand() % (maxX - minX) + minX);
		const float yPosition = (float)(rand() % (maxY - minY) + minY);
		const float speed = (float)(rand() % (speedMax - speedMin) + speedMin);

		SCloudData cloudData = {{xPosition, yPosition, (float)cloudWidthScaled, (float)cloudHeightScaled}, speed, 150};
		clouds.push_back(cloudData);
	}
}