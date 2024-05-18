#include "Game.h"

int main(int arg, const char* argv[]) 
{
	Game game("FirstEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game.IsRunning()) 
	{
		game.Update();
		game.Render();
	}
	return 0;
}