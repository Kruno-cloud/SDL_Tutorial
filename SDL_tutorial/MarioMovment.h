#pragma once
#ifndef MARIOMOVEMENT_H
#define MARIOMOVEMENT_H

#include <SDL.h>

void PomicanjeMariaLijevoDesno(SDL_Keycode key, float& marioAccX, int& marioState);
void PomicanjeMarijaGore(SDL_Keycode key, float& marioVelY, bool& onGround, int& marioState);

#endif 