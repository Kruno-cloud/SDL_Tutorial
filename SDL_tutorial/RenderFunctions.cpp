#include "RenderFunctions.h"
#include "SDLWrappers.h"  

void RenderScene(SDLRenderer_Wrapper& sdlRenderer,
    SDLTexture_Wrapper& marioTexture, SDL_Rect& marioRect,
    SDLTexture_Wrapper& blockTexture, int blockWidth, int blockHeight,
    SDLTexture_Wrapper& pipeTexture, SDL_Rect& pipeRect1,
    SDLTexture_Wrapper& pipeTexture2, SDL_Rect& pipeRect2,
    SDLTexture_Wrapper& treePlatform, SDL_Rect& treePlatfromRect) {

    // Prikaz Marija
    sdlRenderer.TextureCopy(marioTexture.GetTexture(), NULL, &marioRect);

    // Računanje broja blokova koji stanu u širinu prozora
    int numBlocks = 1280 / blockWidth;

    // Renderiranje blokova ispod Marija
    for (int i = 0; i < numBlocks; i++) {
        SDL_Rect blockRect = { i * blockWidth, 550, blockWidth, blockHeight };
        sdlRenderer.TextureCopy(blockTexture.GetTexture(), NULL, &blockRect);
    }

    // Renderiranje cijevi i platformi
    sdlRenderer.TextureCopy(pipeTexture.GetTexture(), NULL, &pipeRect1);
    sdlRenderer.TextureCopy(pipeTexture2.GetTexture(), NULL, &pipeRect2);
    sdlRenderer.TextureCopy(treePlatform.GetTexture(), NULL, &treePlatfromRect);

    // Prezentacija renderiranih elemenata
    sdlRenderer.Present();
}
