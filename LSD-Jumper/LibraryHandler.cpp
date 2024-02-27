#include "LibraryHandler.h"

#include <SDL.h>
#include <iostream>

LibraryHandler::LibraryHandler()
{
	
}

LibraryHandler::~LibraryHandler()
{

}

bool LibraryHandler::Create()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL failed to initialize! " << SDL_GetError();

		return false;
	}

	// Initialize SDL_Image (for loading images/textures)
	// Initialize SDL_TTF (for font files for rendering text)
	// Initialize SDL_Mixer (for loading music and/or sounds)

	return true;
}

void LibraryHandler::Destroy()
{
	// NOTE: do the destroying in the oposite way of how they were initialize
	// This is a good programming habit to remember

	// Shutdown SDL_Mixer (for loading music and/or sounds)
	// Shutdown SDL_TTF (for font files for rendering text)
	// Shutdown SDL_Image (for loading images/textures)

	// Shutdown SDL
	SDL_Quit();
}