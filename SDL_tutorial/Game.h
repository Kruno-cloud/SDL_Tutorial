#include <iostream>
#include <memory>
#include <SDL.h>
#undef main

class Game
{
public:
	Game() = delete;
	Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();
	
	void Update();
	void Render();
	
	bool IsRunning() { return m_isRunning;  }

private:
	int m_cnt = 0;
	bool m_isRunning = false;
	
	struct SDLWindowWrapper
	{
	public:
		SDLWindowWrapper(const char* title, int xpos, int ypos, int width, int height, int flags)
		{
			m_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		}
		~SDLWindowWrapper()
		{
			if (m_Window)
			{
				SDL_DestroyWindow(m_Window);
			}
		}
		SDLWindowWrapper(SDLWindowWrapper& wrapper) = delete;
		SDL_Window* m_Window;
	};

	std::unique_ptr<SDLWindowWrapper> m_Window;
	SDL_Renderer* m_renderer;


	void HandleEvents();
};

