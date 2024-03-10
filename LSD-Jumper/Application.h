#pragma once

#include "AudioHandler.h"
#include "FontHandler.h"
#include "InputHandler.h"
#include "LibraryHandler.h"
#include "State.h"
#include "TextureHandler.h"
#include "Timer.h"
#include "Window.h"

class Application 
{
public:

	enum EState
	{
		MENU = 0,
		GAME,
		GAME_OVER,
		NUM_STATES
	};

public:

	 Application();
	~Application() {}

	bool Create();
	void Destroy();
	void Run();
	void HandleEvents();
	void Update();
	void Render();

	bool SetState(const int newState);

	void EndRound(const int score);

public:

	// Getters/Setters

	TextureHandler* GetTextureHandler() {return textureHandler;}
	FontHandler* GetFontHandler() {return fontHandler;}
	AudioHandler* GetAudioHandler() {return audioHandler;}
	InputHandler* GetInputHandler() {return inputHandler;}

	Window* GetWindow() { return window; }

	TTF_Font* GetDefaultFont() {return defaultFont;}

	int GetHighestScore() {return highestScore;}

	void Quit() {running = false;}

private:

	LibraryHandler* libraryHandler = nullptr;
	TextureHandler* textureHandler = nullptr;
	FontHandler* fontHandler = nullptr;
	AudioHandler* audioHandler = nullptr;
	InputHandler* inputHandler = nullptr;

	Window* window = nullptr;

	TTF_Font* defaultFont = nullptr;

	State* states[NUM_STATES] = {nullptr};
	State* currentState = nullptr;
	State* nextState = nullptr;

	Timer timer;

	int highestScore = 0;

	bool running = true;

};