#pragma once
#include "SDLWrappers.h"

bool initializeSDL(SDL_Wrapper& sdlWrapper);
bool createWindow(SDLWindow_Wrapper& sdlWindow);
bool createRenderer(SDLRenderer_Wrapper& sdlRenderer, SDLWindow_Wrapper& sdlWindow);
bool loadTexture(SDLTexture_Wrapper& texture, const char* filePath, SDLRenderer_Wrapper& sdlRenderer);
