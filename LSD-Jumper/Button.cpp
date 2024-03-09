#include "Button.h"

void Button::Create(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, const SDL_Color& backgroundColor, const SDL_Color& textColor, const SDL_Color& textColorHovered)
{
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), { 255, 255, 255, 255 });
	if (!surface)
		return;

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	if (!texture)
		return;

	int textureWidth = 0;
	int textureHeight = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

	rect = {0.0f, 0.0f, (float)textureWidth, (float)textureHeight};
	bgColor = backgroundColor;
	txtColor = textColor;
	txtColorHovered = textColorHovered;
}

void Button::Destroy()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Button::Render(SDL_Renderer* renderer, const float mouseXPosition, const float mouseYPosition)
{
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRectF(renderer, &rect);

	const SDL_Color textColor = (PointInside(mouseXPosition, mouseYPosition) ? txtColorHovered : txtColor);
	SDL_SetTextureColorMod(texture, textColor.r, textColor.g, textColor.b);
	SDL_RenderCopyF(renderer, texture, nullptr, &rect);
}

bool Button::PointInside(const float xPosition, const float yPosition)
{
	const SDL_FPoint mousePosition = { xPosition, yPosition };
	return (SDL_PointInFRect(&mousePosition, &rect) == SDL_TRUE);
}
