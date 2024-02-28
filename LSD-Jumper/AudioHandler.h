#pragma once 

#include "SDL_mixer.h"
#include <string>

class AudioHandler 
{
public: 
	AudioHandler() {}
	~AudioHandler() {}

	Mix_Chunk* CreateAudio(const std::string& audioName);
	Mix_Music* CreateMusic(const std::string& musicName);

	void DestroyAudio(Mix_Chunk* chunk);
	void DestroyMusic(Mix_Music* music);
};