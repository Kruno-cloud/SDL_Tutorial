#pragma once
#include "RenderFunctions.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class SDL_Wrapper
{
public:
    SDL_Wrapper(Uint32 flags);
    ~SDL_Wrapper();
    bool IsInitilized();

private:
    bool m_Initilized = false;
};

class SDLWindow_Wrapper
{
public:
    SDLWindow_Wrapper(const char* title, int posX, int posY, int width, int height, Uint32 flags);
    ~SDLWindow_Wrapper();
    bool IsInitilized();
    SDL_Window& GetWindow();

private:
    SDL_Window* m_Window = nullptr;
};

class SDLRenderer_Wrapper
{
public:
    SDLRenderer_Wrapper(SDL_Window* window, int index, Uint32 flags);
    ~SDLRenderer_Wrapper();
    bool IsInitilized();
    SDL_Renderer& GetRenderer();
    void TextureCopy(SDL_Texture& texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
    void Present();

private:
    SDL_Renderer* m_Renderer = nullptr;
};

class SDLTexture_Wrapper
{
public:
    SDLTexture_Wrapper(const char* path, SDL_Renderer& renderer);
    ~SDLTexture_Wrapper();
    bool IsInitilized();
    SDL_Texture& GetTexture();

private:
    SDL_Texture* m_Texture = nullptr;
};
