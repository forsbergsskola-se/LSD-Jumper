#pragma once

#include "LibraryHandler.h"
#include "Window.h"
#include "Timer.h"
#include "Game.h"

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
	Timer timer; 
	Game* game;

	bool running = true;

};