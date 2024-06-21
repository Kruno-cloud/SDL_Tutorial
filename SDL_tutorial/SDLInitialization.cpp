#include "SDLInitialization.h"
#include <iostream>

bool initializeSDL(SDL_Wrapper& sdlWrapper) {
    if (!sdlWrapper.IsInitilized()) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool createWindow(SDLWindow_Wrapper& sdlWindow) {
    if (!sdlWindow.IsInitilized()) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool createRenderer(SDLRenderer_Wrapper& sdlRenderer, SDLWindow_Wrapper& sdlWindow) {
    if (!sdlRenderer.IsInitilized()) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool loadTexture(SDLTexture_Wrapper& texture, const char* filePath, SDLRenderer_Wrapper& sdlRenderer) {
    if (!texture.IsInitilized()) {
        std::cerr << "Unable to load texture! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}
