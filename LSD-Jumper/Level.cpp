#include "Level.h"
#include "Application.h"

// std::sort
#include <algorithm>
#include <stdlib.h>

bool Level::Create(Application* mainApplication)
{
	application = mainApplication;

	cloud = application->GetTextureHandler()->CreateTexture("Assets/Textures/cloud.png");
	if (!cloud)
		return false;

	const float windowWidth = (float)application->GetWindow()->GetWidth();
	const float windowHeight = (float)application->GetWindow()->GetHeight();

	int cloudWidth = 0;
	int cloudHeight = 0;
	SDL_QueryTexture(cloud, nullptr, nullptr, &cloudWidth, &cloudHeight);

	// Seed the random number generator
	srand((unsigned int)time(NULL));

	const int numClouds = 5;

	renderRects.resize(numClouds);
	colliders.resize(numClouds);

	const int min = (int)(-cloudWidth * 1.5f);
	const int max = (int)( cloudWidth * 1.5f);
	float previousCloudXPosition = (windowWidth * 0.5f) - (cloudWidth * 0.5f);
	float previousCloudYPosition = (float)(windowHeight - (cloudHeight * 2.0f));

	for(int i = 0; i < numClouds; i++)
	{
		const float colliderHeight = cloudHeight * 0.2f;

		if(i == 0)
		{
			renderRects[i] = {previousCloudXPosition, previousCloudYPosition, (float)cloudWidth, (float)cloudHeight};
			colliders[i] = {previousCloudXPosition, previousCloudYPosition + ((cloudHeight * 0.5f) - (colliderHeight * 0.5f)), (float)cloudWidth, colliderHeight};
		}

		else
		{
			const int xPosition = rand() % (max - min) + min;

			renderRects[i] = {previousCloudXPosition + (float)xPosition, previousCloudYPosition, (float)cloudWidth, (float)cloudHeight};

			// Change this so that the cloud spawns on the other side of the window or something similar
				 if(renderRects[i].x < 0.0f)						renderRects[i].x = 0.0f;
			else if(renderRects[i].x > (windowWidth - cloudWidth))	renderRects[i].x = windowWidth - cloudWidth;

			colliders[i] = {renderRects[i].x, renderRects[i].y + ((cloudHeight * 0.5f) - (colliderHeight * 0.5f)), (float)cloudWidth, colliderHeight};
		}

		previousCloudYPosition -= (float)(cloudHeight * 2.5f);
	}

	return true;
}

void Level::Destroy()
{
	colliders.clear();
	renderRects.clear();

	application->GetTextureHandler()->DestroyTexture(cloud);
}

void Level::Update(const SDL_FRect& cameraRect, const float deltaTime)
{
	const float windowWidth = (float)application->GetWindow()->GetWidth();
	bool anyCloudRespawned = false;

	for(int i = 0; i < renderRects.size(); i++)
	{
		SDL_FRect& renderRect = renderRects[i];
		SDL_FRect& collider = colliders[i];

	//	renderRect.y += cloudFallSpeed * deltaTime;
	//	collider.y = (renderRect.y + (renderRect.h * 0.5f)) - (collider.h * 0.5f);

		if(renderRect.y > (cameraRect.y + cameraRect.h))
		{
			const SDL_FRect lastCloud = renderRects[renderRects.size() - 1];
			const int min = (int)(-renderRect.w * 2.0f);
			const int max = (int)( renderRect.w * 2.0f);
			const int xOffset = rand() % (max - min) + min;

			renderRect.x = lastCloud.x + (float)xOffset;
			renderRect.y = lastCloud.y - (renderRect.h * 2.5f);

				 if(renderRect.x < 0.0f)							renderRect.x = 0.0f;
			else if(renderRect.x > (windowWidth - renderRect.w))	renderRect.x = windowWidth - renderRect.w;

			collider.x = renderRect.x;
			collider.y = renderRect.y + ((renderRect.h * 0.5f) - (collider.h * 0.5f));

			anyCloudRespawned = true;
		}
	}

	if(anyCloudRespawned)
	{
		auto compareFn = [this](const SDL_FRect& rFirst, const SDL_FRect& rSecond) -> bool
		{
			return (rFirst.y > rSecond.y);
		};

		std::sort(renderRects.begin(), renderRects.end(), compareFn);
		std::sort(colliders.begin(), colliders.end(), compareFn);
	}
}

void Level::Render(SDL_Renderer* renderer, const SDL_FRect& cameraRect)
{
	for (SDL_FRect& renderRect : renderRects)
	{
		SDL_FRect renderRectWorld = {renderRect.x - cameraRect.x, renderRect.y - cameraRect.y, renderRect.w, renderRect.h};

		SDL_RenderCopyF(renderer, cloud, nullptr, &renderRectWorld);
	}

	// Only for debugging
	for (SDL_FRect& collider : colliders)
	{
		SDL_FRect colliderWorld = {collider.x - cameraRect.x, collider.y - cameraRect.y, collider.w, collider.h};

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRectF(renderer, &colliderWorld);
	}
}