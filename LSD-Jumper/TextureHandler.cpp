#include "TextureHandler.h"
#include "LibraryHandler.h"
#include "Window.h"

using namespace std;


SDL_Texture* TextureHandler::CreateTexture(const char* imagePath) 
{
    SDL_Renderer* renderer = Window::GetRenderer();
    if (!renderer) 
    {
        cout << "Failed to obtain renderer." << endl;
        return nullptr;
    }

    SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);
    if (!texture) 
    {
        cout << "Failed to load texture: " << IMG_GetError() << endl;
        return nullptr;
    }
    CreateTexture("Image.png");

    return texture;
}


