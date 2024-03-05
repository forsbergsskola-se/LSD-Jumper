#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
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

	void RenderText(TTF_Font* font, const std::string& text, const float xPosition, const float yPosition, const SDL_Color& color);

	SDL_Renderer* GetRenderer() {return renderer;}

	int GetWidth() {return width;}
	int GetHeight() {return height;}

private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int width = 0;
	int height = 0;

};