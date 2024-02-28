#include "Window.h"

Window::Window()
{
	
}
Window::~Window()
{

}


bool Window::Create()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	window = SDL_CreateWindow("LSD-Jumper", // Title of the SDL window 
		SDL_WINDOWPOS_CENTERED, //Position x of the window 
		SDL_WINDOWPOS_CENTERED, // Position y of the window 
		WIDTH, // Width of the window in pixels 
		HEIGHT, // Height of the window in pixels 
		SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN); // Additional flag(s) 


	if (!window)
	{
		std::cout << "Window not created! " << SDL_GetError();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		std::cout << "Renderer failed! " << SDL_GetError();
		return false;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	return true;
}
void Window::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Window::BeginRender()
{
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);
}

void Window::EndRender()
{
	SDL_RenderPresent(renderer);
}
