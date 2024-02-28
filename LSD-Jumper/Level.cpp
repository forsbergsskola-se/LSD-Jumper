#include "Level.h"
#include "Application.h"

Level::Level()
{
}

Level::~Level()
{
}

bool Level::Create(Application* mainApplication)
{
	application = mainApplication;

	cloud = application->GetTextureHandler()->CreateTexture("Assets/Textures/cloud.png");
	if (!cloud)
	{
		return false;
	}

	return true;
}

void Level::Destroy()
{
	application->GetTextureHandler()->DestroyTexture(cloud);
}

void Level::Update(const float deltaTime)
{

}

void Level::Render(SDL_Renderer* renderer)
{
	SDL_FRect rect = { 200,200,272,62 };
	SDL_FRect rect1 = { 400,100,272,62 };
	SDL_FRect rect2 = { 500,300,272,62 };
	SDL_FRect rect3 = { 1000,500,272,62 };

	SDL_RenderCopyF(renderer, cloud, nullptr, &rect);
	SDL_RenderCopyF(renderer, cloud, nullptr, &rect1);
	SDL_RenderCopyF(renderer, cloud, nullptr, &rect2);
	SDL_RenderCopyF(renderer, cloud, nullptr, &rect3);

}
