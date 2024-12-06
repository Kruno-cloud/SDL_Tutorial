#pragma once

#ifndef	RENDERFUNCTIONS_H
#define RENDERFUNCTIONS_H

#include "SDLWrappers.h"
#include "SDL.h"


void RenderScene(SDLRenderer_Wrapper& sdlRenderer,
    SDLTexture_Wrapper& marioTexture, SDL_Rect& marioRect,
    SDLTexture_Wrapper& blockTexture, int blockWidth, int blockHeight,
    SDLTexture_Wrapper& pipeTexture, SDL_Rect& pipeRect1,
    SDLTexture_Wrapper& pipeTexture2, SDL_Rect& pipeRect2,
    SDLTexture_Wrapper& treePlatform, SDL_Rect& treePlatfromRect);
#endif 

