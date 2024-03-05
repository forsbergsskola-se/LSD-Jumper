#pragma once

#include <SDL.h>
#include <vector>

class Application;

class Level
{
public:

	 Level() {}
	~Level() {}

	bool Create(Application* application);
	void Destroy();
	void Update(const SDL_FRect& cameraRect, const float deltaTime);
	void Render(SDL_Renderer* renderer, const SDL_FRect& cameraRect);

	const std::vector<SDL_FRect>& GetColliders() {return colliders;}

private:

	Application* application = nullptr;
	SDL_Texture* cloud = nullptr;

	float cloudFallSpeed = 32.0f;

	std::vector<SDL_FRect> renderRects;
	std::vector<SDL_FRect> colliders;

};