#pragma once
#include <SDL.h> 
#include <SDL_ttf.h>
#include <string>

class Button
{
public:

	 Button() {}
	~Button() {}

	void Create(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, const SDL_Color& backgroundColor, const SDL_Color& textColor, const SDL_Color& textColorHovered);
	void Destroy();
	void Render(SDL_Renderer* renderer, const float mouseXPosition, const float mouseYPosition);

	bool PointInside(const float xPosition, const float yPosition);

	void SetPosition(const float xPosition, const float yPosition) { rect.x = xPosition; rect.y = yPosition; }

	float GetWidth() { return rect.w; }
	float GetHeight() { return rect.h; }

private:

	SDL_Texture* texture = nullptr;
	SDL_FRect rect = { 0.0f, 0.0f, 0.0f, 0.0f};

	SDL_Color bgColor = { 100, 100, 100, 255 };
	SDL_Color txtColor = { 255, 255, 255, 255 };
	SDL_Color txtColorHovered = { 255, 0, 0, 255 };
};

