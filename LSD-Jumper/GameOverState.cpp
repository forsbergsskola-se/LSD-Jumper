#include "GameOverState.h"

#include "Application.h"
#include "InputHandler.h"

bool GameOverState::Create(Application* mainApplication)
{
	std::cout << "Creating game-over state" << std::endl;

	// Create objects that should created once and should persist during the lifetime of the game

	application = mainApplication;

	return true;
}

void GameOverState::Destroy()
{
	std::cout << "Destroying game-over state" << std::endl;

	// Destroy objects that has been created once and should be destroyed in the end of the game's lifetime

	application = nullptr;
}

bool GameOverState::OnEnter()
{
	std::cout << "Entering game-over state" << std::endl;

	// Create objects that should be created/started when this state is entered/started (create textures, load/start game-over music etc)

	backgroundTexture = application->GetTextureHandler()->CreateTexture("Assets/Textures/gameover.png");
	if (!backgroundTexture)
		return false;

	music = application->GetAudioHandler()->CreateMusic("Assets/Audio/gameover.mp3");
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

	const int highestScore = application->GetHighestScore();
	std::string scoreString = "";

	if(highestScore == 0)
		scoreString = "You got 0 points, bummer!";

	else
		scoreString = "Your highest score is: " + std::to_string(application->GetHighestScore()) + "!";

	scoreBox.Create(renderer, defaultFont, scoreString, {0, 0, 0, 0,}, buttonTextColor, buttonTextColor);
	scoreBox.SetPosition(windowWidth - (scoreBox.GetWidth() * 0.5f), windowHeight - (scoreBox.GetHeight() * 0.5f));

	restartButton.Create(renderer, defaultFont, "Restart", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	restartButton.SetPosition(windowWidth - (restartButton.GetWidth() * 0.5f), windowHeight + (restartButton.GetHeight() + 50.0f));
	quitButton.Create(renderer, defaultFont, "Quit", buttonBackgroundColor, buttonTextColor, buttonTextHoveredColor);
	quitButton.SetPosition(windowWidth - (quitButton.GetWidth() * 0.5f), windowHeight + (quitButton.GetHeight() + 120.0f));

	return true;
}

void GameOverState::OnExit()
{
	std::cout << "Exiting game-over state" << std::endl;

	// Destroy objects that should be destroyed/stopped when this state is exited/stopped (destroy textures, unload/stop game-over music etc)

	quitButton.Destroy();
	restartButton.Destroy();
	scoreBox.Destroy();

	Mix_HaltMusic();
	application->GetAudioHandler()->DestroyMusic(music);
	music = nullptr;

	application->GetTextureHandler()->DestroyTexture(backgroundTexture);
	backgroundTexture = nullptr;
}

void GameOverState::Update(const float deltaTime)
{
	InputHandler* inputHandler = application->GetInputHandler();

	if (restartButton.PointInside(inputHandler->GetMouseXPosition(), inputHandler->GetMouseYPosition()) && inputHandler->MouseButtonPressed(SDL_BUTTON_LEFT))
		application->SetState(Application::EState::GAME);

	if (quitButton.PointInside(inputHandler->GetMouseXPosition(), inputHandler->GetMouseYPosition()) && inputHandler->MouseButtonPressed(SDL_BUTTON_LEFT))
		application->Quit();
}

void GameOverState::Render()
{
	SDL_Renderer* renderer = application->GetWindow()->GetRenderer();
	InputHandler* inputHandler = application->GetInputHandler();
	const float mouseXPosition = inputHandler->GetMouseXPosition();
	const float mouseYPosition = inputHandler->GetMouseYPosition();

	SDL_RenderCopyF(renderer, backgroundTexture, nullptr, nullptr);

	scoreBox.Render(renderer, 0.0f, 0.0f);

	restartButton.Render(renderer, mouseXPosition, mouseYPosition);
	quitButton.Render(renderer, mouseXPosition, mouseYPosition);

//	const std::string highestScoreText = "Highest Score: " + std::to_string((int)application->GetHighestScore());
//	application->GetWindow()->RenderText(GetFont(), highestScoreText, (GetWindow()->GetWidth() * 0.35f), (GetWindow()->GetHeight() * 0.6f), { 0, 0, 0, 255 });
}