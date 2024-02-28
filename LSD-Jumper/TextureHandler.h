#pragma once
#include <SDL.h>

class TextureHandler
{
public:
	TextureHandler() {};
	~TextureHandler() {};
	SDL_Texture* CreateTexture(const char* imagePath);
	void SDL_DestroyTexture(SDL_Texture*);
};