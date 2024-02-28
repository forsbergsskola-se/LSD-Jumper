#pragma once
#include <SDL.h>

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void Update();
	bool KeyPressed(SDL_Scancode keyboardKey);

private:
	bool currentKeyboardState[SDL_NUM_SCANCODES];
	bool prevKeyboardState[SDL_NUM_SCANCODES];
};

