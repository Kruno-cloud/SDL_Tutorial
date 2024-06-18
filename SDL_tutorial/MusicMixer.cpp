#include "MusicMixer.h"
#include <SDL_mixer.h>
#include <iostream>

// Globalna varijabla za zvučni efekt
Mix_Chunk* jumpSound = nullptr;

void MusicMixer::Init() {
    // Inicijalizacija SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    else {
        std::cout << "SDL_mixer initialized successfully." << std::endl;
    }

    // Učitavanje zvučnog efekta
    jumpSound = Mix_LoadWAV("sounds/smb_jump-small.wav");
    if (jumpSound == nullptr) {
        std::cerr << "Failed to load jump sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    else {
        std::cout << "Jump sound effect loaded successfully." << std::endl;
    }
}

void MusicMixer::PlayJumpSound() {
    if (jumpSound != nullptr) {
        Mix_PlayChannel(-1, jumpSound, 0);
    }
    else {
        std::cerr << "Jump sound effect is not loaded." << std::endl;
    }
}

void MusicMixer::CleanUp() {
    if (jumpSound != nullptr) {
        Mix_FreeChunk(jumpSound);
        jumpSound = nullptr;  // Postavljanje pokazivača na nullptr nakon oslobađanja
    }
    Mix_CloseAudio();
}
