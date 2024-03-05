#pragma once

#include "AudioHandler.h"
#include "FontHandler.h"
#include "Game.h"
#include "InputHandler.h"
#include "LibraryHandler.h"
#include "TextureHandler.h"
#include "Timer.h"
#include "Window.h"

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

private:

	LibraryHandler* libraryHandler = nullptr;

	Window* window = nullptr;

	TextureHandler* textureHandler = nullptr;

	FontHandler* fontHandler = nullptr;

	AudioHandler* audioHandler = nullptr;

	InputHandler* inputhandler = nullptr;

	Game* game = nullptr;

	Timer timer;

	bool running = true;

};