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
	int cloudWidth = 0;
	int cloudHeight = 0;
	SDL_QueryTexture(cloud, nullptr, nullptr, &cloudWidth, &cloudHeight);

	const int windowHeight = application->GetWindow()->GetHeight();
	const int windowWight = application->GetWindow()->GetWidth();
	for (size_t i = 0; i < 10; i++)
	{
		const float cloudYStart = (windowHeight - cloudHeight) - 100.0f;
		const float cloudY = cloudYStart - ((cloudHeight + (cloudHeight * 0.5f)) * i);

		const float cloudXStart = (windowWight - cloudWidth);
		const float cloudX = cloudXStart - ((cloudWidth + (cloudWidth * 0.5)) * i);

		SDL_FRect cloudRect = { cloudX, cloudY, 272, 62 };
		cloudPool.push_back(cloudRect);
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
	/*
	SDL_FRect rect = {200,200,272,62};
	SDL_FRect rect1 = { 400,100,272,62 };
	SDL_FRect rect2 = { 500,300,272,62 };
	SDL_FRect rect3 = { 1000,500,272,62 };

	SDL_RenderCopyF(renderer, cloud, nullptr, &rect);
	SDL_RenderCopyF(renderer, cloud, nullptr, &rect1);
	SDL_RenderCopyF(renderer, cloud, nullptr, &rect2);
	SDL_RenderCopyF(renderer, cloud, nullptr, &rect3);
	*/

//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (size_t i = 0; i < cloudPool.size(); i++)
	{
	//	SDL_RenderDrawRectF(renderer, &cloudPool[i]);

		SDL_RenderCopyF(renderer, cloud, nullptr, &cloudPool[i]);
	}
}
