#include "Timer.h"
#include <SDL.h>

void Timer::Update()
{
	startTime = SDL_GetTicks();
	preTime = SDL_GetTicks();
	DeltaTime = (preTime - startTime) * 0.0001;
}
double Timer::getDeltaTime()
{
	return DeltaTime;
}

