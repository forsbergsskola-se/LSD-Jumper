#pragma once

#include "LibraryHandler.h"
#include "Window.h"
#include "Timer.h"
#include "Game.h"
#include "TextureHandler.h"

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

 

private:

	LibraryHandler* libraryHandler = nullptr;

	Window* window = nullptr;

	TextureHandler* textureHandler = nullptr;

	Game* game = nullptr;

	Timer timer;

	bool running = true;

};