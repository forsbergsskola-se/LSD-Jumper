#include "AudioHandler.h"
#include <iostream>

Mix_Chunk* AudioHandler::CreateAudio(const std::string& audioName)
{
	Mix_Chunk* chunk = Mix_LoadWAV(audioName.c_str());
	if (!chunk)
	{
		std::cout << "Failed to load auido " << audioName.c_str() << "" << std::endl;
		std::cout << Mix_GetError() << std::endl;

		return nullptr;
	}
	return chunk;
}

Mix_Music* AudioHandler::CreateMusic(const std::string& musicName)
{
	Mix_Music* music = Mix_LoadMUS(musicName.c_str());
	if (!music)
	{
		std::cout << "Failed to load music " << musicName.c_str() << "" << std::endl;
		std::cout << Mix_GetError() << std::endl;

		return nullptr;
	}
	return music;
}

void AudioHandler::DestroyAudio(Mix_Chunk* chunk)
{
	Mix_FreeChunk(chunk);
}

void AudioHandler::DestroyMusic(Mix_Music* music)
{
	Mix_FreeMusic(music);
}
