#include "AudioHandler.h"

#include <iostream>

Mix_Chunk* AudioHandler::CreateAudio(const std::string& fileName)
{
	Mix_Chunk* chunk = Mix_LoadWAV(fileName.c_str());

	if (!chunk)
	{
		std::cout << "Error: failed to load audio " << fileName.c_str() << "" << std::endl;
		std::cout << Mix_GetError() << std::endl;

		return nullptr;
	}

	return chunk;
}

Mix_Music* AudioHandler::CreateMusic(const std::string& fileName)
{
	Mix_Music* music = Mix_LoadMUS(fileName.c_str());

	if (!music)
	{
		std::cout << "Error: failed to load music " << fileName.c_str() << "" << std::endl;
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
