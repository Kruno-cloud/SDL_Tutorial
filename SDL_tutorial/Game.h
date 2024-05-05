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
	
	// Zasto je handleEvents() public metoda koju zoves iz main-a, to mi je vise za private i da ju zoves na update-u
	void handleEvents();
	void update();
	void render();
	// Koliko vidim, clean se treba pozvati kada se unisti instanca igre, stoga umjesto clean funkcije prebaci kod u dekonstruktor
	void clean();

	// Za funkcije koje ti vracaju state preferiraj prefix Is, kao IsRunning()
	bool running() { return isRunning;  }

private:
	int cnt = 0;
	bool isRunning;
	// Ovo je malo advanced, no ako imas ptr koji treba custom konstruktor(SDL_CreateWindow) i/ili destruktor(SDL_DestroyWindow) probaj ga staviti u strukturu
	//Eg.
	/*
	struct SDLWindowWrapper
	{
		public:
			SDLWindowWrapper(const char* title, int xpos, int ypos, int width, int height, int flags)
			{
				m_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			}
			~SDLWindowWrapper()
			{
				if(m_Window)
				{
					SDL_DestroyWindow(m_Window);
				}
			}
			SDLWindowWrapper(SDLWindowWrapper& wrapper) = delete;
			SDL_Window* m_Window;
	}

	//E sad jer SDL_Window treba lazy init, promijeni SDL_Window* window; u std::unique_ptr<SDLWindowWrapper> m_Window i pozovi make_unique kad ti treba window
	//smart pointer ce ti pozvati dekonstrukror kad klasa ciji je member izađe is scope-a sto je amazing jer svaki put kad ne moras managat memoriju je manja sansa da crashas igru
	// ili leakas memoriju
	*/
	SDL_Window* window;
	SDL_Renderer* renderer;
};

