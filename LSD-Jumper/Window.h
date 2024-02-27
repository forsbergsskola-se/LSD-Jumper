#pragma once

#include <iostream>
#include <SDL.h>

class Window
{
public:
	Window();
	~Window();
	bool Create();
	void Destroy();
	void BeginRender();
	void EndRender();

	SDL_Renderer* GetRenderer() { return renderer; }

private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

};

