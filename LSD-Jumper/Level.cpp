#include "Level.h"
#include "Application.h"
#include <time.h>
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
	int halfCloudWidth = 0.5 * cloudWidth;
	// Seed the random number generator
	srand(time(0));

	const int numClouds = 5;

	renderRects.resize(numClouds);
	colliders.resize(numClouds);

	const int maxOffset = halfCloudWidth * 3;
	const int minOffset = -maxOffset;
	float previousCloudXPosition = (windowWidth * 0.5f) - (halfCloudWidth);
	float previousCloudYPosition = (float)(windowHeight - (cloudHeight * 2.0f));

	for (int i = 0; i < numClouds; i++)
	{
		const float colliderHeight = cloudHeight * 0.2f;

		if (i == 0)
		{
			renderRects[i] = { previousCloudXPosition, previousCloudYPosition, (float)cloudWidth, (float)cloudHeight };
			colliders[i] = { previousCloudXPosition, previousCloudYPosition + ((cloudHeight * 0.5f) - (colliderHeight * 0.5f)), (float)cloudWidth, colliderHeight };
		}

		else
		{
			const int curMin = std::max(0, (int)previousCloudXPosition + minOffset);
			const int curMax = std::min((int)windowWidth-cloudWidth, (int)previousCloudXPosition + maxOffset);

			const int xPosition = rand() % (curMax - curMin) + curMin;

			std::cout << "Cloud #" << i << " between " << curMin << " and " << curMax << ": " << xPosition << std::endl;

			renderRects[i] = { (float)xPosition, previousCloudYPosition, (float)cloudWidth, (float)cloudHeight };

			colliders[i] = { renderRects[i].x, renderRects[i].y + ((cloudHeight * 0.5f) - (colliderHeight * 0.5f)), (float)cloudWidth, colliderHeight };

			previousCloudXPosition = xPosition;
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

	for (int i = 0; i < renderRects.size(); i++)
	{
		SDL_FRect& renderRect = renderRects[i];
		SDL_FRect& collider = colliders[i];

		//CLOUDS FALLING - DOESN'T WORK
		//renderRect.y += cloudFallSpeed * deltaTime;
		//collider.y = (renderRect.y + (renderRect.h * 0.5f)) - (collider.h * 0.5f);

		if (renderRect.y > (cameraRect.y + cameraRect.h))
		{
			int lastIndex = (i - 1 + renderRects.size()) % renderRects.size();
			//std::cout << "Relocating cloud #" << i << " based on position of cloud #" << lastIndex << ".\n";		//debugging stuff
			const SDL_FRect& lastCloud = renderRects[lastIndex ];
			const int maxOffsetX = (lastCloud.w * 0.5f) * 3;
			const int minOffsetX = -maxOffsetX;

			const int curMinX = std::max(0, (int)lastCloud.x + minOffsetX);
			const int curMaxX = std::min((int)(windowWidth - lastCloud.w), (int)lastCloud.x + maxOffsetX);


			//std::cout << "Here, we reposition the cloud with the old code.\n";	//debugging stuff
			const int xPosition = rand() % (curMaxX - curMinX) + curMinX;

			renderRect.x = xPosition;
			renderRect.y = lastCloud.y - (renderRect.h * 2.5f);


			if (renderRect.x < 0.0f)
			{
				renderRect.x = 0.0f;
			}
			else if (renderRect.x > (windowWidth - renderRect.w))
			{
				renderRect.x = windowWidth - renderRect.w;
			}

			collider.x = renderRect.x;
			collider.y = renderRect.y + ((renderRect.h * 0.5f) - (collider.h * 0.5f));

			anyCloudRespawned = true;
		}
	}
}

void Level::Render(SDL_Renderer* renderer, const SDL_FRect& cameraRect)
{
	for (SDL_FRect& renderRect : renderRects)
	{
		SDL_FRect renderRectWorld = { renderRect.x - cameraRect.x, renderRect.y - cameraRect.y, renderRect.w, renderRect.h };

		SDL_RenderCopyF(renderer, cloud, nullptr, &renderRectWorld);
	}

	// Only for debugging
	/*
	for (SDL_FRect& collider : colliders)
	{
		SDL_FRect colliderWorld = {collider.x - cameraRect.x, collider.y - cameraRect.y, collider.w, collider.h};

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRectF(renderer, &colliderWorld);
	}
	*/
}