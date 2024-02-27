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

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;



};

