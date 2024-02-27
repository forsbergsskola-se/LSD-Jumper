#pragma once

#include "LibraryHandler.h"
#include "Window.h"

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

	bool running = true;

};