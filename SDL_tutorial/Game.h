#include <iostream>
#include "SDL.h"

// Zasto pragma once u headeru?, Generalno zelis da se deklaracije(.h) pojave u vise kompilacijskih jedinica a definicije(.cpp) ne 
#pragma once
// Imenovanje je all over the place pa hajmo mi kreirati standard
// sve klase, strukture, funkcije neka budu PascalCase
// svi argumenti camelCase
// sve variable camelCase s prefixom m_, eg. m_MemberVariabla
class Game
{
public:
	Game();
	~Game();
	
	// Koliko vidim init se poziva na kreaciji igre, stoga ga prebaci u konstruktor
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	// Koliko vidim, clean se treba pozvati kada se unisti instanca igre, stoga umjesto clean funkcije prebaci kod u dekonstruktor
	void clean();


	bool running() { return isRunning;  }

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;


};

