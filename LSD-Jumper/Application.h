#pragma once

#include "AudioHandler.h"
#include "FontHandler.h"
#include "Game.h"
#include "InputHandler.h"
#include "LibraryHandler.h"
#include "TextureHandler.h"
#include "Timer.h"
#include "Window.h"
#include "Button.h"

class Application 
{
public:

	 Application() {}
	~Application() {}

	bool Create();
	void Destroy();
	void Run();
	void HandleEvents();
	void Update();
	void Render();
	void Quit() { running = false; }
	void UpdateHighestScore(float score);

	Window* GetWindow() { return window; }

	TextureHandler* GetTextureHandler() { return textureHandler; }

	FontHandler* GetFontHnadler() { return fontHandler; }

	AudioHandler* GetAudioHandler() { return audioHandler; }

	InputHandler* GetInputHandler() { return inputhandler; }

	TTF_Font* GetFont() { return font; }
	TTF_Font* GetNameFont() { return nameFont; }
	TTF_Font* GetCreditsFont() { return creditsFont; }

	int volume = 2; //=================================================== SET THE VOLUME OF THE MUSIC AND THE JUMP SOUND!!!

public:
	enum State
	{
		Menu = 0,
		Play,
		Dead
	};

	State curState = State::Menu;

private:

	SDL_Texture* gameOver = nullptr;

	SDL_Texture* start = nullptr;

	LibraryHandler* libraryHandler = nullptr;

	Window* window = nullptr;

	TextureHandler* textureHandler = nullptr;

	FontHandler* fontHandler = nullptr;

	AudioHandler* audioHandler = nullptr;

	Mix_Music* menuMusic = nullptr;

	Mix_Music* gameMusic = nullptr;

	Mix_Music* gameOverMusic = nullptr;

	InputHandler* inputhandler = nullptr;

	Game* game = nullptr;

	TTF_Font* font = nullptr;

	TTF_Font* nameFont = nullptr;

	TTF_Font* creditsFont = nullptr;

	Player* player = nullptr;
		
	Timer timer;


	Button startGameButton;
	Button restartGameButton;
	Button quitButton;


	bool running = true;

	bool gameOverMusicPlaying = false;

	float highestScore = 0.0f;


};