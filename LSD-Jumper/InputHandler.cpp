#include "InputHandler.h"

InputHandler::InputHandler()
{
	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		currentKeyboardState[i] = false;
		prevKeyboardState[i] = false;
	}
}

InputHandler::~InputHandler()
{

}

void InputHandler::Update()
{
	int mouseX = 0;
	int mouseY = 0;
	const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

	for (size_t i = 0; i < 8; i++)
	{
		prevMouseState[i] = curMouseState[i];
		curMouseState[i] = ((mouseState & SDL_BUTTON(i)) ? true : false);
	}

	mouseXPosition = (float)mouseX;
	mouseYPosition = (float)mouseY;

	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		prevKeyboardState[i] = currentKeyboardState[i];
		currentKeyboardState[i] = (keyboardState[i] == SDL_TRUE);
	}
}

bool InputHandler::KeyPressed(SDL_Scancode keyboardKey)
{
	return (currentKeyboardState[keyboardKey] && !prevKeyboardState[keyboardKey]);
}

bool InputHandler::KeyHeld(SDL_Scancode keyboardKey)
{
	return currentKeyboardState[keyboardKey];
}

bool InputHandler::MouseButtonPressed(const int mouseButton)
{
	return (curMouseState[mouseButton] && !prevMouseState[mouseButton]);
}
