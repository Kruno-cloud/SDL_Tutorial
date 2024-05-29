#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


// Konstantne za kretanje i gravitaciju
const int MARIO_SPEED = 1;
const int JUMP_HEIGHT = 20;
const int GRAVITY = 1;


// Funkcija za provjeru preklapanja dva pravokutnika
bool checkCollision(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w <= b.x || a.x >= b.x + b.w || a.y + a.h <= b.y || a.y >= b.y + b.h) {
        return false;
    }
    return true;
}




int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Simple SDL Frame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 1024, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Učitavanje pozadine
    SDL_Surface* backgroundSurface = IMG_Load("textures/CloudsBackround.png");
    if (!backgroundSurface) {
        std::cerr << "Unable to load background image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Učitavanje Marija
    SDL_Surface* marioSurface = IMG_Load("textures/mario.png");
    if (!marioSurface) {
        std::cerr << "Unable to load Mario image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* marioTexture = SDL_CreateTextureFromSurface(renderer, marioSurface);
    SDL_FreeSurface(marioSurface);

    // Učitavanje bloka
    SDL_Surface* blockSurface = IMG_Load("textures/block.png");
    if (!blockSurface) {
        std::cerr << "Unable to load block image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(marioTexture);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* blockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);
    SDL_FreeSurface(blockSurface);


    // Učitavanje 1. cijevi 
    SDL_Surface* pipeSurface = IMG_Load("textures/pipe.png");
    if (!pipeSurface) {
        std::cerr << "Unable to load pipe image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(blockTexture);
        SDL_DestroyTexture(marioTexture);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* pipeTexture = SDL_CreateTextureFromSurface(renderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);

    // Učitavanje 2. cijevi
    SDL_Surface* pipeSurface2 = IMG_Load("textures/pipe2.png");
    if (!pipeSurface2) {
        std::cerr << "Unable to load pipe image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(pipeTexture);
        SDL_DestroyTexture(blockTexture);
        SDL_DestroyTexture(marioTexture);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* pipeTexture2 = SDL_CreateTextureFromSurface(renderer, pipeSurface2);
    SDL_FreeSurface(pipeSurface2);


    // Početne pozicije i brzine Marija
    int marioX = 0, marioY = 500;
    int marioVelX = 0, marioVelY = 0;
    bool onGround = true;


    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    marioVelX = -MARIO_SPEED;
                    break;
                case SDLK_RIGHT:
                    marioVelX = MARIO_SPEED;
                    break;
                case SDLK_UP:
                    if (onGround) {
                        marioVelY = -JUMP_HEIGHT;
                        onGround = false;
                    }
                    break;
                }
            }
            else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    marioVelX = 0;
                    break;
                }
            }
        }

        // Ažuriranje pozicije Marija
        marioX += marioVelX;
        marioY += marioVelY;

        // Ažuriranje gravitacije 
        if (!onGround) {
            marioVelY += GRAVITY;
        }


        SDL_Rect marioRect = { marioX, marioY, 64, 64 };
        SDL_Rect pipeRect1 = { 400, 450, 64, 100 }; // Primjer položaja i veličine cijevi 
        SDL_Rect pipeRect2 = { 800, 450, 64, 100 };

        // Provjera kolizije s vrhom cijevi
        if (checkCollision(marioRect, pipeRect1)) {
            if (marioY + 64 <= pipeRect1.y + 10) {  // Provjera da li je Mario iznad cijevi
                marioY = pipeRect1.y - 64;
                marioVelY = 0;
                onGround = true;
            }
        }
        if (checkCollision(marioRect, pipeRect2)) {
            if (marioY + 64 <= pipeRect2.y + 10) {  // Provjera da li je Mario iznad cijevi
                marioY = pipeRect2.y - 64;
                marioVelY = 0;
                onGround = true;
            }
        }



        // Provjera dali je Mario na zemlji ( jednostavna logika ) 
        if (marioY >= 500) {
            marioY = 500;
            marioVelY = 0;
            onGround = true;
        }

        SDL_RenderClear(renderer);

        // Renderiranje  pozadine 
        if (backgroundTexture) {
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        }
        else {
            std::cerr << "Background texture is null!" << std::endl;
        }

        // Definiranje veličine prikaza Marija 1.Način
        /*SDL_Rect marioRect;
        marioRect.x = 0;   // postavljanje x pozicije Marija
        marioRect.y = 500; // postavljanje y pozicije Marija
        marioRect.h = 64;  // postavljanje visine Marija
        marioRect.w = 64;  // postavljanje širine Marija*/

       

        // Renderaj Marija s novom veličinom
        SDL_RenderCopy(renderer, marioTexture, NULL, &marioRect);




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
            SDL_RenderCopy(renderer, blockTexture, NULL, &blockRect);

        }

        // Renderiranje cijevi, pipe.png
        //SDL_Rect pipeRect1 = { 400, 450, 64, 100 }; // Primjer položaja i veličine cijevi 
        //SDL_RenderCopy(renderer, pipeTexture, NULL, &pipeRect1);


        // Renderiranje druge cijevi, pipe2.png
        //SDL_Rect pipeRect2 = { 800, 450, 64, 100 };
        //SDL_RenderCopy(renderer, pipeTexture2, NULL, &pipeRect2);

        SDL_RenderCopy(renderer, pipeTexture, NULL, &pipeRect1);
        SDL_RenderCopy(renderer, pipeTexture2, NULL, &pipeRect2);

        SDL_RenderPresent(renderer);

        
    }

    SDL_DestroyTexture(blockTexture);
    SDL_DestroyTexture(marioTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyTexture(pipeTexture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
