#pragma once

#include "Button.h"
#include "State.h"

#include <SDL_mixer.h>
#include <vector>

class MenuState : public State
{
public:

	 MenuState(void) {}
	~MenuState(void) {}

	virtual bool Create(Application* mainApplication) override;
	virtual void Destroy() override;
	virtual bool OnEnter() override;
	virtual void OnExit() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() override;

private:

	void SpawnClouds();

private:

	SDL_Texture* backgroundTexture = nullptr;
	SDL_Texture* cloudTexture = nullptr;

	Mix_Music* music = nullptr;

	float lifeTime = 0.0f;
	float backgroundOffset = 0.0f;

	struct SCloudData
	{
		SDL_FRect rect = {0.0f, 0.0f, 0.0f, 0.0f};
		float speed = 0.0f;
		Uint8 alpha = 255;
	};

	std::vector<SCloudData> clouds;

	Button LSDJumperTextBox;
	Button startGameButton;
	Button quitButton;

};