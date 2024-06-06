#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDLWrappers.h>
#include <cassert>


// Konstante za kretanje i gravitaciju
const int JUMP_HEIGHT = 2;
const float GRAVITY = 1.0f;
const float MAX_FALL_SPEED = 10.0f;
const float MAX_SPEED = 5.0f;
const float ACCELERATION = 1.0f;

// Varijable za animacije
const int FRAME_IDLE = 0;
const int FRAME_RUN = 1;
const int FRAME_JUMP = 2;
const int ANIMATION_SPEED = 10;

// Funkcija za provjeru preklapanja dva pravokutnika
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



constexpr int ERROR_RETURN_CODE = 1;

int main(int argc, char* args[]) {
    SDL_Wrapper initilizeSDLLib(SDL_INIT_VIDEO);
    if (initilizeSDLLib.IsInitilized() == false)
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

    SDLTexture_Wrapper backgroundTexture("textures/CloudsBackround.png", sdlRenderer.GetRenderer());
    if (backgroundTexture.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLTexture_Wrapper marioTexture("textures/mario.png", sdlRenderer.GetRenderer());
    if (marioTexture.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLTexture_Wrapper blockTexture("textures/block.png", sdlRenderer.GetRenderer());
    if (blockTexture.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLTexture_Wrapper pipeTexture("textures/pipe.png", sdlRenderer.GetRenderer());
    if (pipeTexture.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLTexture_Wrapper pipeTexture2("textures/pipe2.png", sdlRenderer.GetRenderer());
    if (pipeTexture2.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }

    SDLTexture_Wrapper treePlatform("textures/treePlatform.png", sdlRenderer.GetRenderer());
    if (treePlatform.IsInitilized() == false)
    {
        return ERROR_RETURN_CODE;
    }


   
    // Početne pozicije i brzine Marija
    float marioX = 0, marioY = 500;
    float marioVelX = 0.0f, marioVelY = 0.0f;
    float marioAccX = 0.0f;
    bool onGround = true;

    // Varijable za animaciju
    int marioState = FRAME_IDLE;
    int frame = 0;
    int frameCounter = 0;


    bool quit = false;
    SDL_Event e;


    // Varijable za pracenje vremena 
    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    float deltaTime;



    while (!quit) {
        // Izracunavanje delta vremena
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // DeltaTime u sekundama
        lastTime = currentTime;

 
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                       // marioVelX = -MARIO_SPEED;
                        marioAccX = -ACCELERATION;
                        marioState = FRAME_RUN;
                        break;
                    case SDLK_RIGHT:
                        marioAccX = ACCELERATION;
                        marioState = FRAME_RUN;
                        break;
                    case SDLK_UP:
                        if (onGround) {
                            marioVelY = -JUMP_HEIGHT;
                            onGround = false;
                            marioState = FRAME_JUMP;
                        }
                        break;
                    }
                }
                else if (e.type == SDL_KEYUP) {
                    switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        // marioVelX = 0; ovaj dio je promjenjen nakon sto su dodane animacije
                        marioAccX = 0;
                        if (onGround) {
                            marioState = FRAME_IDLE;
                        }
                        break;


                    }
                }
        }

        // Povecaj frame za 1, osiugravajuci da se ponavlja unutar opsega animacije 
        frame++;
        if (frame / ANIMATION_SPEED >= 3) {
        frame = 0;
        }


        // Azuriranje brzine Marija, dodano nakon stvaranja animacija za Marija
        marioVelX += marioAccX * deltaTime;
        if (marioVelX > MAX_SPEED) marioVelX = MAX_SPEED;
        if (marioVelX < -MAX_SPEED) marioVelX = -MAX_SPEED;


        // Ažuriranje pozicije Marija koristeći deltaTime
        marioX += static_cast<float>(marioVelX * deltaTime * 100);
        marioY += static_cast<float> (marioVelY * deltaTime * 100);

        // Ažuriranje gravitacije 
        if (!onGround) {
            marioVelY += GRAVITY * deltaTime;
            if (marioVelY > MAX_FALL_SPEED) {
                marioVelY = MAX_FALL_SPEED;
            }
        }


        SDL_Rect marioRect = { marioX, marioY, 64, 64 };
        SDL_Rect pipeRect1 = { 400, 450, 64, 100 }; // Primjer položaja i veličine cijevi 
        SDL_Rect pipeRect2 = { 800, 450, 64, 100 };
        SDL_Rect treePlatfromRect = { 1000, 450, 64, 100 };

        // Provjera kolizije s vrhom cijevi i Marija
        if (checkCollision(marioRect, pipeRect1)) {
            if (marioY + 64 <= pipeRect1.y + 10) {  // Provjera da li je Mario iznad cijevi
                marioY = pipeRect1.y - 64;
                marioVelY = 0;
                onGround = false;
            }
        }
        if (checkCollision(marioRect, pipeRect2)) {
            if (marioY + 64 <= pipeRect2.y + 10) {  // Provjera da li je Mario iznad cijevi
                marioY = pipeRect2.y - 64;
                marioVelY = 0;
                onGround = false;
            }
        }

        if (checkCollision(marioRect, treePlatfromRect)) {
            if (marioY + 64 <= treePlatfromRect.y + 10) { // Provejra dali je Mario iznad platforme drvo
                marioY = treePlatfromRect.y - 64;
                marioVelY = 0;
                onGround = false;
            }
        }


        // Provjera dali je Mario na zemlji ( jednostavna logika ) 
        if (marioY >= 500) {
            marioY = 500;
            marioVelY = 0;
            onGround = true;
        }

        SDL_RenderClear(&sdlRenderer.GetRenderer());

        sdlRenderer.TextureCopy(backgroundTexture.GetTexture(), NULL, NULL);

        // Definiranje veličine prikaza Marija 1.Način
        /*SDL_Rect marioRect;
        marioRect.x = 0;   // postavljanje x pozicije Marija
        marioRect.y = 500; // postavljanje y pozicije Marija
        marioRect.h = 64;  // postavljanje visine Marija
        marioRect.w = 64;  // postavljanje širine Marija*/

        // Postavljanje izvora frame-a za animaciju Marija 
        SDL_Rect srcRect;
        switch (marioState) {
        case FRAME_IDLE:
            srcRect = { (frame * ANIMATION_SPEED) % 3 * 64,0,64,64 };
            break;
        case FRAME_RUN:
            srcRect = { (frame * ANIMATION_SPEED) % 3 * 64, 64, 64, 64 };
            break;
        case FRAME_JUMP:
            srcRect = { (frame * ANIMATION_SPEED) % 3 * 64, 128, 64, 64 };
            break;
        }

        sdlRenderer.TextureCopy(marioTexture.GetTexture(), NULL, &marioRect);

        // Računanje broja blokova koji stanu u širinu prozora
        int blockWidth = 50;  // Stvarna širina slike bloka
        int blockHeight = 50;
        int numBlocks = 1280 / blockWidth;  // Broj blokova koji stanu u širinu prozora







        // Renderiranje blokova ispod Marija 1.Način
        /*for (int i = 0; i < numBlocks; i++) {
            SDL_Rect blockRect;
            blockRect.x = i * blockWidth; // postavljanje x pozicije bloka
            blockRect.y = 550;            // postavljanje y pozicije bloka
            blockRect.w = blockWidth;     // Širina bloka
            blockRect.h = blockHeight;    // Visina bloka

            SDL_RenderCopy(renderer, blockTexture, NULL, &blockRect);
        }*/

        // Renderiranje blokova ispod Marija 2.Način
        for (int i = 0; i < numBlocks; i++) {
            SDL_Rect blockRect = { i * blockWidth, 550, blockWidth, blockHeight };
            sdlRenderer.TextureCopy(blockTexture.GetTexture(), NULL, &blockRect);
        }

        // Renderiranje cijevi, pipe.png
        //SDL_Rect pipeRect1 = { 400, 450, 64, 100 }; // Primjer položaja i veličine cijevi 
        //SDL_RenderCopy(renderer, pipeTexture, NULL, &pipeRect1);


        // Renderiranje druge cijevi, pipe2.png
        //SDL_Rect pipeRect2 = { 800, 450, 64, 100 };
        //SDL_RenderCopy(renderer, pipeTexture2, NULL, &pipeRect2);

        sdlRenderer.TextureCopy(pipeTexture.GetTexture(), NULL, &pipeRect1);
        sdlRenderer.TextureCopy(pipeTexture2.GetTexture(), NULL, &pipeRect2);
        sdlRenderer.TextureCopy(treePlatform.GetTexture(), NULL, &treePlatfromRect);
        sdlRenderer.Present();
    }


    return 0;
}
