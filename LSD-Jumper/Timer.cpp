#include "Timer.h"
#include <SDL.h>
#include <utility>

void Timer::Update()
{
	startTime = SDL_GetTicks();
	deltaTime = std::min((startTime - preTime) * 0.001, 0.25);
	preTime = startTime;
}