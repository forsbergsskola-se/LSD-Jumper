#pragma once

#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_mixer.h>
#include <SDL_ttf.h>


class LibraryHandler
{
public:

	LibraryHandler();
	~LibraryHandler();

	bool Create();
	void Destroy();
};

