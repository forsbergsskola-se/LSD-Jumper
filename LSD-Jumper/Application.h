#pragma once

#include "LibraryHandler.h"
#include "Window.h"
#include "Timer.h"
#include "Game.h"
#include "TextureHandler.h"
#include "FontHandler.h"
#include "AudioHandler.h"

class Application 
{
public:

	Application();
	~Application();

	bool Create();
	void Destroy();
	void Run();
	void HandleEvents();
	void Update();
	void Render();

	TextureHandler* GetTextureHandler() { return textureHandler; }

	FontHandler* GetFontHnadler() { return fontHandler; }

	AudioHandler* GetAudioHandler() { return audioHandler; }
private:

	LibraryHandler* libraryHandler = nullptr;

	Window* window = nullptr;

	TextureHandler* textureHandler = nullptr;

	FontHandler* fontHandler = nullptr;

	AudioHandler* audioHandler = nullptr;

	Game* game = nullptr;

	Timer timer;

	bool running = true;

};