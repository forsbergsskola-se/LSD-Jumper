#include "TextureHandler.h"

#include <SDL_image.h>
#include <iostream>

bool TextureHandler::Create(SDL_Renderer* SDLRenderer)
{
	renderer = SDLRenderer;

	return true;
}

void TextureHandler::Destroy()
{
	renderer = nullptr;
}

SDL_Texture* TextureHandler::CreateTexture(const std::string& fileName)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, fileName.c_str());

	if (!texture)
	{
		std::cout << "Error: failed to load texture" << std::endl;
		std::cout << IMG_GetError() << std::endl;

		return nullptr;
	}

	return texture;
}

void TextureHandler::DestroyTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
}