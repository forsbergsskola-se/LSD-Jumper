#include "Window.h"

bool Window::Create()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	window = SDL_CreateWindow("LSD-Jumper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "Error: failed to create SDL window! " << SDL_GetError();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		std::cout << "Error: failed to create SDL renderer! " << SDL_GetError();
		return false;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	width = WIDTH;
	height = HEIGHT;

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
