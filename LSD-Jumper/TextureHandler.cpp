#include "TextureHandler.h"

#include <iostream>
#include <SDL_image.h>

TextureHandler::TextureHandler()
{

}

TextureHandler::~TextureHandler()
{

}

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
		std::cout << "Failed to load texture " << fileName.c_str() << "" << std::endl;
		std::cout << IMG_GetError() << std::endl;

		return nullptr;
	}

	return texture;
}

void TextureHandler::DestroyTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
}