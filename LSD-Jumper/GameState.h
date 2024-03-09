#pragma once

#include "Button.h"
#include "Camera.h"
#include "Level.h"
#include "Player.h"
#include "State.h"

#include <SDL_mixer.h>

class GameState final : public State
{
public:

	 GameState(void) {}
	~GameState(void) {}

	virtual bool Create(Application* mainApplication) override;
	virtual void Destroy() override;
	virtual bool OnEnter() override;
	virtual void OnExit() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

private:

	SDL_Texture* backgroundTexture = nullptr;

	Level* level = nullptr;

	Player* player = nullptr;

	Camera* camera = nullptr;

	Mix_Music* music = nullptr;

	Button menuButton;
	Button quitButton;

};