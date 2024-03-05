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

	Window* GetWindow() { return window; }

	TextureHandler* GetTextureHandler() { return textureHandler; }

	FontHandler* GetFontHnadler() { return fontHandler; }

	AudioHandler* GetAudioHandler() { return audioHandler; }

	InputHandler* GetInputHandler() { return inputhandler; }

	TTF_Font* GetFont() { return font; }

private:

	enum State
	{
		Menu = 0,
		Play,
		Dead
	};

private:

	LibraryHandler* libraryHandler = nullptr;

	Window* window = nullptr;

	TextureHandler* textureHandler = nullptr;

	FontHandler* fontHandler = nullptr;

	AudioHandler* audioHandler = nullptr;

	InputHandler* inputhandler = nullptr;

	Game* game = nullptr;

	TTF_Font* font = nullptr;
		
	Timer timer;

	Button startGameButton;
	Button quitButton;

	State curState = State::Menu;

	bool running = true;

};