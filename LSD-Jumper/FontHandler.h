#pragma once

#include <SDL_ttf.h>
#include <string>

class FontHandler 
{
public:

	 FontHandler() {}
	~FontHandler() {}

	TTF_Font* CreateFont(const std::string& fileName, const int textSize);
	void DestroyFont(TTF_Font* font);

};

