#include "Timer.h"
#include <SDL.h>

void Timer::Update()
{
	startTime = SDL_GetTicks();
	deltaTime = (startTime - preTime) * 0.001;
	preTime = startTime;
}