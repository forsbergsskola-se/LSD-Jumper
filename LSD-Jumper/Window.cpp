#include "Window.h"

bool Window::Create()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	window = SDL_CreateWindow("LSD-Jumper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
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

void Window::RenderText(TTF_Font* font, const std::string& text, const float xPosition, const float yPosition, const SDL_Color& color)
{
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), { 255, 255, 255, 255 });
	if (!surface)
		return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	SDL_FreeSurface(surface);
	
	if (!texture)
		return;

	int textureWidth = 0;
	int textureHeight = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

	const SDL_FRect rect = {xPosition, yPosition, textureWidth, textureHeight};

	SDL_RenderCopyF(renderer, texture, nullptr, &rect);

	SDL_DestroyTexture(texture);
}