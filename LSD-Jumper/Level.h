#pragma once

#include <vector>
#include <SDL.h>

class Application;

class Level
{
public:
	Level();
	~Level();
	bool Create(Application* application);
	void Destroy();
	void Update(const float deltaTime);
	void Render(SDL_Renderer* renderer, const SDL_FRect& cameraRect);

private:

	Application* application = nullptr;
	std::vector<SDL_FRect>  cloudPool;
	SDL_Texture* cloud = nullptr;
	std::vector<SDL_FRect> cloudColliders;

};

