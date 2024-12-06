#include "MarioMovment.h"
#include <SDL_mixer.h>
#include <MusicMixer.h>


// Konstante za kretanje i gravitaciju
const int JUMP_HEIGHT = 2;
const float GRAVITY = 8.0f;
const float MAX_FALL_SPEED = 7.0f;
const float MAX_SPEED = 5.0f;
const float ACCELERATION = 1.0f;


// Varijable za animacije
const int FRAME_IDLE = 0;
const int FRAME_RUN = 1;
const int FRAME_JUMP = 2;
const int ANIMATION_SPEED = 10;

// Varijable za animaciju
int marioState = FRAME_IDLE;
int frame = 0;
int frameCounter = 0;


void PomicanjeMariaLijevoDesno(SDL_Keycode key, float& marioAccX, int& marioState) {
    switch (key) {
    case SDLK_LEFT:
        marioAccX = -ACCELERATION;
        marioState = FRAME_RUN;
        break;
    case SDLK_RIGHT:
        marioAccX = ACCELERATION;
        marioState = FRAME_RUN;
        break;
    default:
        break;
    }
}

void PomicanjeMarijaGore(SDL_Keycode key, float& marioVelY, bool& onGround, int& marioState) {
    if (key == SDLK_UP && onGround) {
        marioVelY = -JUMP_HEIGHT;
        onGround = false;
        marioState = FRAME_JUMP;
        MusicMixer::PlayJumpSound();
    }
}