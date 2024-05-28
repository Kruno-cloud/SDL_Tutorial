#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Simple SDL Frame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
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
    

    // Ucitavanje Marija
    SDL_Surface* marioSurface = IMG_Load("mario.png");
    if (!marioSurface) {
        std::cerr << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* marioTexture = SDL_CreateTextureFromSurface(renderer, marioSurface);
    SDL_FreeSurface(marioSurface);


    // Ucitavanje bloka
    SDL_Surface* blockSurface = IMG_Load("block.png");
    if (!blockSurface) {
        std::cerr << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;

    }
    SDL_Texture* blockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);
    SDL_FreeSurface(blockSurface);



    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);

        //Renderaj Marija
        SDL_RenderCopy(renderer, marioTexture, NULL, NULL);


        //Renderaj blok ispod Marija
        SDL_Rect blockRect;
        blockRect.x = 0; // postavljanje x pozicije bloka
        blockRect.y = 100; // postavljanje y pozicije bloka
        blockRect.w = 50; // Širina bloka
        blockRect.h = 50; // Visina bloka


        SDL_RenderCopy(renderer, blockTexture, NULL, &blockRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(blockTexture);
    SDL_DestroyTexture(marioTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
