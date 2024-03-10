#include "GameState.h"

#include "Application.h"
#include "InputHandler.h"

bool GameState::Create(Application* mainApplication)
{
	std::cout << "Creating game state" << std::endl;

	// Create objects that should created once and should persist during the lifetime of the game

	application = mainApplication;

	return true;
}

void GameState::Destroy()
{
	std::cout << "Destroying game state" << std::endl;

	// Destroy objects that has been created once and should be destroyed in the end of the game's lifetime

	application = nullptr;
}

bool GameState::OnEnter()
{
	std::cout << "Entering game state" << std::endl;

	// Create objects that should be created/started when this state is entered/started (create textures, load/start game music, load sounds etc)

	Window* window = application->GetWindow();
	SDL_Renderer* renderer = window->GetRenderer();
	const float windowWidth = (float)window->GetWidth();
	const float windowHeight = (float)window->GetHeight();

	backgroundTexture = application->GetTextureHandler()->CreateTexture("Assets/Textures/game.png");
	if (!backgroundTexture)
		return false;

	level = new Level;
	if (!level->Create(application))
		return false;

	player = new Player;
	if (!player->Create(application))
		return false;

	camera = new Camera;
	camera->Create(windowWidth, windowHeight);

	music = application->GetAudioHandler()->CreateMusic("Assets/Audio/game.mp3");
	if (!music)
		return false;
	Mix_PlayMusic(music, -1);

	TTF_Font* defaultFont = application->GetDefaultFont();
	const SDL_Color buttonBackgroundColor = { 100, 100, 100, 255 };
	const SDL_Color buttonTextColor = { 255, 255, 255, 255 };
	const SDL_Color buttonTextHoveredColor = { 255, 0, 0, 255 };

	menuButton.Create(renderer, defaultFont, "Menu", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	menuButton.SetPosition(5.0f, windowHeight - (menuButton.GetHeight() + 60.0f));
	quitButton.Create(renderer, defaultFont, "Quit", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	quitButton.SetPosition(5.0f, windowHeight - (quitButton.GetHeight() + 5.0f));

	return true;
}

void GameState::OnExit()
{
	std::cout << "Exiting game state" << std::endl;

	// Destroy objects that should be destroyed/stopped when this state is exited/stopped (destroy textures, unload/stop game music, unload sounds etc)

	quitButton.Destroy();
	menuButton.Destroy();

	Mix_HaltMusic();
	application->GetAudioHandler()->DestroyMusic(music);
	music = nullptr;

	delete camera;
	camera = nullptr;

	player->Destroy();
	delete player;
	player = nullptr;

	level->Destroy();
	delete level;
	level = nullptr;

	application->GetTextureHandler()->DestroyTexture(backgroundTexture);
	backgroundTexture = nullptr;
}

void GameState::Update(const float deltaTime)
{
	InputHandler* inputHandler = application->GetInputHandler();
	const float mouseXPosition = inputHandler->GetMouseXPosition();
	const float mouseYPosition = inputHandler->GetMouseYPosition();

	if (menuButton.PointInside(mouseXPosition, mouseYPosition) && inputHandler->MouseButtonPressed(SDL_BUTTON_LEFT))
		application->SetState(Application::EState::MENU);

	if (quitButton.PointInside(mouseXPosition, mouseYPosition) && inputHandler->MouseButtonPressed(SDL_BUTTON_LEFT))
		application->Quit();

	if(inputHandler->KeyPressed(SDL_SCANCODE_ESCAPE))
		application->Quit();

	level->Update(camera->GetRect(), deltaTime);
	player->Update(deltaTime, level->GetColliders());
	camera->Update(player, deltaTime);

	const SDL_FRect cameraRect = camera->GetRect();

	if (player->GetYPosition() > ((cameraRect.y + cameraRect.h) - player->GetCollider().h))
		application->EndRound((int)player->GetScore());
}

void GameState::Render()
{
	SDL_Renderer* renderer = application->GetWindow()->GetRenderer();
	InputHandler* inputHandler = application->GetInputHandler();
	const SDL_FRect cameraRect = camera->GetRect();
	const float mouseXPosition = inputHandler->GetMouseXPosition();
	const float mouseYPosition = inputHandler->GetMouseYPosition();

	SDL_RenderCopyF(renderer, backgroundTexture, nullptr, nullptr);

	player->Render(renderer, cameraRect);

	level->Render(renderer, cameraRect);

	const std::string highestScoreText = "Score: " + std::to_string((int)player->GetScore());
	application->GetWindow()->RenderText(application->GetDefaultFont(), highestScoreText, 5.0f, 5.0f, { 0, 0, 0, 255 });

	menuButton.Render(renderer, mouseXPosition, mouseYPosition);
	quitButton.Render(renderer, mouseXPosition, mouseYPosition);
}