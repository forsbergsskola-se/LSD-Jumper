#include "LibraryHandler.h"

#include <SDL.h>
#include <SDL_image.h>    
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

bool LibraryHandler::Create()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Error: failed to initialize SDL! " << SDL_GetError();

		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "Error: failed to initialize SDL_Image! " << IMG_GetError();

		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error: failed to initialize SDL_TTF! " << TTF_GetError();

		return false;
	}

	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0)
	{
		std::cout << "Error: failed to initialize SDL_Mixer! " << Mix_GetError();

		return false;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
	{
		std::cout << "Error: failed to open audio device! " << Mix_GetError();

		return false;
	}

	return true;
}

void LibraryHandler::Destroy()
{
	Mix_Quit();	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}