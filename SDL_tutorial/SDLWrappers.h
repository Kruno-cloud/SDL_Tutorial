#pragma once

class SDL_Wrapper
{
public:
    SDL_Wrapper(Uint32 flags)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            m_Initilized = true;
        }
    }
    ~SDL_Wrapper()
    {
        if (m_Initilized)
        {
            SDL_Quit();
        }
    }
    bool IsInitilized() { return m_Initilized; }
private:
    bool m_Initilized = false;
};

class SDLWindow_Wrapper
{
public:
    SDLWindow_Wrapper(const char* title, int posX, int posY, int width, int height, Uint32 flags)
    {
        m_Window = SDL_CreateWindow(title, posX, posY, width, height, flags);
        if (m_Window == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
    ~SDLWindow_Wrapper()
    {
        if (m_Window)
        {
            SDL_DestroyWindow(m_Window);
        }
    }
    bool IsInitilized() { return m_Window != nullptr; }
    SDL_Window& GetWindow() { return *m_Window; };
private:
    SDL_Window* m_Window = nullptr;
};

class SDLRenderer_Wrapper
{
public:
    SDLRenderer_Wrapper(SDL_Window* window, int index, Uint32 flags)
    {
        m_Renderer = SDL_CreateRenderer(window, index, flags);
        if (m_Renderer == nullptr) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
    ~SDLRenderer_Wrapper()
    {
        if (m_Renderer)
        {
            SDL_DestroyRenderer(m_Renderer);
        }
    }
    bool IsInitilized() { return m_Renderer != nullptr; }
    SDL_Renderer& GetRenderer() { return *m_Renderer; };
    void TextureCopy(SDL_Texture& texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) { SDL_RenderCopy(m_Renderer, &texture, srcrect, dstrect); }
    void Present() { SDL_RenderPresent(m_Renderer); };
private:
    SDL_Renderer* m_Renderer = nullptr;
};

class SDLTexture_Wrapper
{
public:
    SDLTexture_Wrapper(const char* path, SDL_Renderer& renderer)
    {
        SDL_Surface* surface = IMG_Load(path);
        if (surface == nullptr) {
            std::cerr << "Unable to load background image! IMG_Error: " << IMG_GetError() << std::endl;
            return;
        }
        m_Texture = SDL_CreateTextureFromSurface(&renderer, surface);
        SDL_FreeSurface(surface);
    }
    ~SDLTexture_Wrapper()
    {
        if (m_Texture)
        {
            SDL_DestroyTexture(m_Texture);
        }
    }
    bool IsInitilized() { return m_Texture != nullptr; }
    SDL_Texture& GetTexture() { return *m_Texture; };
private:
    SDL_Texture* m_Texture = nullptr;
};