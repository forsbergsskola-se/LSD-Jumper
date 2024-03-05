#pragma once

#include <SDL.h>
#include <iostream>

class Window
{
public:

	 Window() {}
	~Window() {}

	bool Create();
	void Destroy();
	void BeginRender();
	void EndRender();

	SDL_Renderer* GetRenderer() {return renderer;}

	int GetWidth() {return width;}
	int GetHeight() {return height;}

private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int width = 0;
	int height = 0;

};