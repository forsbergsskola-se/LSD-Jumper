#include "Window.h"

Window::Window()
{
	
}
Window::~Window()
{

}

bool Window::Create()
{
	int WIDTH = 800;
	int HEIGHT = 600;
	window = SDL_CreateWindow("LSD-Jumpper", // Title of the SDL window 
		SDL_WINDOWPOS_CENTERED, //Position x of the window 
		SDL_WINDOWPOS_CENTERED, // Position y of the window 
		WIDTH, // Width of the window in pixels 
		HEIGHT, // Height of the window in pixels 
		SDL_WINDOW_SHOWN); // Additional flag(s) 


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