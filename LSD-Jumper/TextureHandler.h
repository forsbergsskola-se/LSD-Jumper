#pragma once

#include <SDL.h>
#include <string>

class TextureHandler
{
public:

	TextureHandler();
	~TextureHandler();

	bool Create(SDL_Renderer* SDLRenderer);
	void Destroy();

	SDL_Texture* CreateTexture(const std::string& fileName);
	void DestroyTexture(SDL_Texture* texture);

private:

	SDL_Renderer* renderer = nullptr;

};