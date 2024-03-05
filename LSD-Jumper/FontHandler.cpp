#include "FontHandler.h"
#include <iostream>

TTF_Font* FontHandler::CreateFont(const std::string& fileName, const int textSize)
{
	TTF_Font* font = TTF_OpenFont(fileName.c_str(), textSize);

	if (!font)
	{
		std::cout << "Error: failed to load font " << fileName.c_str() << "" << std::endl;
		std::cout << TTF_GetError() << std::endl;

		return nullptr;
	}

	return font;
}

void FontHandler::DestroyFont(TTF_Font* font)
{
	TTF_CloseFont(font);
}