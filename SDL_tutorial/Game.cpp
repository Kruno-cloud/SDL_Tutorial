#include "Game.h"

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return;
	}

	m_Window = std::make_unique<SDLWindowWrapper>(title, xpos, ypos, width, height, flags);
	//ako ne dobijes valid window ne bih rekao da ti igra radi aka isRunning == true
	if (m_Window->m_Window == nullptr)
	{
		return;
	}
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	std::cout << " Renderer created! " << std::endl;
	m_isRunning = true;
}
Game::~Game()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
	HandleEvents();
}

void Game::Render()
{
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}