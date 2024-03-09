#pragma once

#include "Button.h"
#include "Camera.h"
#include "Level.h"
#include "Player.h"
#include "State.h"

class GameOverState: public State
{
public:

	 GameOverState(void) {}
	~GameOverState(void) {}

	virtual bool Create(Application* mainApplication) override;
	virtual void Destroy() override;
	virtual bool OnEnter() override;
	virtual void OnExit() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

private:

	SDL_Texture* backgroundTexture = nullptr;

	Mix_Music* music = nullptr;

	Button scoreBox;
	Button restartButton;
	Button quitButton;

};