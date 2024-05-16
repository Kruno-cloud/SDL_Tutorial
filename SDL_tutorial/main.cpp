#include "Game.h"

// Ne treba ti globalna variabla, generalno probaj uciniti sve u svojoj moci da ne koristis globalne variable u svome programu.
// Globalne variable su jedino korisne kad ti treba singleton, a singleton je pattern koji je rijetko potreban
Game* game = nullptr;

int main(int arg, const char* argv[]) 
{
	// zasto kreiras ptr ovdje? Game game; works just fine
	game = new Game();

	// nazovi argumente svojih funkcija. eg.
	// static constexpr std::string windowTitle = "FirstEngine"
	// static constexpr int windowWidth = 800
	// puno lakse za citati jer ne moram znati sto init funkcija treba
	game->Init("FirstEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while (game->IsRunning()) {
		game->HandleEvents();
		game->Update();
		game->Render();
	}
	game->clean();
	return 0;
}