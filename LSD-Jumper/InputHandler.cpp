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
