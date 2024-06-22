#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDLWrappers.h>
#include <MusicMixer.h>
#include "SDLInitialization.h"
#include "MarioMovment.h"
#include "RenderFunctions.h"
#include <cassert>

// Constants for movement and gravity
const int JUMP_HEIGHT = 2;
const float GRAVITY = 8.0f;
const float MAX_FALL_SPEED = 7.0f;
const float MAX_SPEED = 5.0f;
const float ACCELERATION = 1.0f;

// Animation variables
const int FRAME_IDLE = 0;
const int FRAME_RUN = 1;
const int FRAME_JUMP = 2;
const int ANIMATION_SPEED = 10;

// Function to check collision between two rectangles
bool checkCollision(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w <= b.x || a.x >= b.x + b.w || a.y + a.h <= b.y || a.y >= b.y + b.h) {
        return false;
    }
    return true;
}

template <typename CastFrom, typename CastTo>
CastTo LukinSafeCast(CastFrom from)
{
    CastTo cast = static_cast<CastTo>(from);
    assert(from == static_cast<CastFrom>(cast) && "bad cast");
    return cast;
}

// Calculate delta time
void izracunDeltaVremena(Uint32& lastTime, Uint32& currentTime, float& deltaTime) {
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f; // DeltaTime in seconds
    lastTime = currentTime;
}

constexpr int ERROR_RETURN_CODE = 1;

int main(int argc, char* args[])
{
    SDL_Wrapper sdlWrapper(SDL_INIT_VIDEO);
    if (sdlWrapper.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLWindow_Wrapper sdlWindow("Simple SDL Frame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 1024, SDL_WINDOW_SHOWN);
    if (sdlWindow.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLRenderer_Wrapper sdlRenderer(&sdlWindow.GetWindow(), -1, SDL_RENDERER_ACCELERATED);
    if (sdlRenderer.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLTexture_Wrapper backgroundTexture("textures/CloudsBackround.png", sdlRenderer);
    if (backgroundTexture.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLTexture_Wrapper marioTexture("textures/CloudsBackround.png", sdlRenderer);
    if (marioTexture.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }
    //copy paste za ostale
    /*
    SDLTexture_Wrapper backgroundTexture, marioTexture, blockTexture, pipeTexture, pipeTexture2, treePlatform;
    if (!loadTexture(backgroundTexture, "textures/CloudsBackround.png", sdlRenderer)) return ERROR_RETURN_CODE;
    if (!loadTexture(marioTexture, "textures/mario.png", sdlRenderer)) return ERROR_RETURN_CODE;
    if (!loadTexture(blockTexture, "textures/block.png", sdlRenderer)) return ERROR_RETURN_CODE;
    if (!loadTexture(pipeTexture, "textures/pipe.png", sdlRenderer)) return ERROR_RETURN_CODE;
    if (!loadTexture(pipeTexture2, "textures/pipe2.png", sdlRenderer)) return ERROR_RETURN_CODE;
    if (!loadTexture(treePlatform, "textures/treePlatform.png", sdlRenderer)) return ERROR_RETURN_CODE;
    */

    // Pozcije i brzine Marija 
    float marioX = 0, marioY = 500;
    float marioVelX = 0.0f, marioVelY = 0.0f;
    float marioAccX = 0.0f;
    bool onGround = true;

    // Animacijske varijable
    int marioState = FRAME_IDLE;
    int frame = 0;
    int frameCounter = 0;

    MusicMixer::Init();
    bool quit = false;
    SDL_Event e;

    // Varijabla za praćenje vremena
    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    float deltaTime;

    int blockWidth = 50;
    int blockHeight = 50;

    SDL_Rect marioRect = { static_cast<int>(marioX), static_cast<int>(marioY), 64, 64 };
    SDL_Rect pipeRect1 = { 400, 450, 64, 100 }; // Example position and size of pipes
    SDL_Rect pipeRect2 = { 800, 450, 64, 100 };
    SDL_Rect treePlatfromRect = { 1000, 450, 64, 100 };

    auto isOnGround = [&marioRect, &pipeRect1, &pipeRect2, &treePlatfromRect]() {
        return checkCollision(marioRect, pipeRect1) ||
            checkCollision(marioRect, pipeRect2) ||
            checkCollision(marioRect, treePlatfromRect);
        };

    while (!quit) {
        izracunDeltaVremena(lastTime, currentTime, deltaTime);
        onGround = isOnGround();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                PomicanjeMariaLijevoDesno(static_cast<SDL_Keycode>(e.key.keysym.sym), marioAccX, marioState);
                PomicanjeMarijaGore(static_cast<SDL_Keycode>(e.key.keysym.sym), marioVelY, onGround, marioState);
            }
            else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    marioAccX = 0;
                    if (onGround) {
                        marioState = FRAME_IDLE;
                    }
                    break;
                }
            }
        }

       
        // Povecanje frame za jedan
        frame++;
        if (frame / ANIMATION_SPEED >= 3) {
            frame = 0;
        }

     
        // Povecanje brzine Marija, poslije dodavanja animacija za Marija
        marioVelX += marioAccX * deltaTime;
        if (marioVelX > MAX_SPEED) marioVelX = MAX_SPEED;
        if (marioVelX < -MAX_SPEED) marioVelX = -MAX_SPEED;

        // Update poziije Marija koristeći delta time 
        marioX += static_cast<float>(marioVelX * deltaTime * 500);
        marioY += static_cast<float>(marioVelY * deltaTime * 500);

        // Gravitacija

        if (!onGround) {
            marioVelY += GRAVITY * deltaTime;
            if (marioVelY > MAX_FALL_SPEED) {
                marioVelY = MAX_FALL_SPEED;
            }
        }

        SDL_RenderClear(&sdlRenderer.GetRenderer());
        sdlRenderer.TextureCopy(backgroundTexture.GetTexture(), NULL, NULL);

        // Rendering cijevi, platformi i Marija
        SDL_Rect destRect;

        // Render pipeRect1
        destRect = { pipeRect1.x, pipeRect1.y, pipeRect1.w, pipeRect1.h };
        sdlRenderer.TextureCopy(pipeTexture.GetTexture(), NULL, &destRect);

        // Render pipeRect2
        destRect = { pipeRect2.x, pipeRect2.y, pipeRect2.w, pipeRect2.h };
        sdlRenderer.TextureCopy(pipeTexture2.GetTexture(), NULL, &destRect);

        // Render treePlatform
        destRect = { treePlatfromRect.x, treePlatfromRect.y, treePlatfromRect.w, treePlatfromRect.h };
        sdlRenderer.TextureCopy(treePlatform.GetTexture(), NULL, &destRect);

        // Render Mario
        destRect = { static_cast<int>(marioX), static_cast<int>(marioY), marioRect.w, marioRect.h };
        sdlRenderer.TextureCopy(marioTexture.GetTexture(), NULL, &destRect);

        sdlRenderer.Present();
    }

    MusicMixer::CleanUp();
    return 0;
}
