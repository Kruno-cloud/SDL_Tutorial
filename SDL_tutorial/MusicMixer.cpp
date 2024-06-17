#include "MusicMixer.h"
#include <SDL_mixer.h>
#include <iostream>

Mix_Chunk* jumpSound = nullptr;

void MusicMixer::Init() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	jumpSound = Mix_LoadWAV("sounds/smb_jump-small.wav");
	if (jumpSound == nullptr) {
		std::cerr << "Failed to load jump sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
	}

void MusicMixer::PlayJumpSound() {
	if (jumpSound != nullptr) {
		Mix_PlayChannel(-1, jumpSound, 0);

	}
}

void MusicMixer::CleanUp() {
	if (jumpSound != nullptr) {
		Mix_FreeChunk(jumpSound);
	}
	Mix_CloseAudio();
}


