//includovi kojima je path ovisan o tome gdje je file-a su po meni evil jer se kod uvijek prebacuje iz foldera u folder
//preferiraj #include <...> jer je on relativan naspram tvog project root-a(mozda ces morati include paths modificirati u konfiguraciji projekta no sumnjam)
#include "Game.h"

// Samo kao info pogledaj rule of 3 ili 5 ili 7
Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		//ako ne dobijes valid window ne bih rekao da ti igra radi aka isRunning == true
		if (window)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << " Renderer created! " << std::endl;

		}
		isRunning = true;
	} else {
		// makni else condition, inicializitaj ovu variablu na false u deklaraciji ili konstruktoru
		isRunning = false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	cnt++;
	std::cout << cnt << std:: endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
