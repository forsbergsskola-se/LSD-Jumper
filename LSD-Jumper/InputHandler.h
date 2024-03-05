#pragma once

#include <SDL.h>

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void Update();
	bool KeyPressed(SDL_Scancode keyboardKey);
	bool KeyHeld(SDL_Scancode keyboardKey);

	bool MouseButtonPressed(const int mouseButtonS);

	float GetMouseXPosition() { return mouseXPosition; }
	float GetMouseYPosition() { return mouseYPosition; }

private:

	float mouseXPosition = 0.0f;
	float mouseYPosition = 0.0f;

	bool currentKeyboardState[SDL_NUM_SCANCODES];
	bool prevKeyboardState[SDL_NUM_SCANCODES];

	bool curMouseState[8];
	bool prevMouseState[8];

};