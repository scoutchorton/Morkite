#include <iostream>

#include <SDL2/SDL.h>
#include <lua5.4/lua.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/*
Resources

SDL Tutorials: https://lazyfoo.net/tutorials/SDL/index.php
*/

SDL_Window* initSDL() {
	SDL_Window* window = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	window = SDL_CreateWindow("PROJECT MORKITE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL) {
		std::cerr << "Window initialization error: " << SDL_GetError() << std::endl;
		return NULL;
	}

	return window;
}

void quitSDL(SDL_Window* window) {
	if(window != NULL)
		SDL_DestroyWindow(window);

	SDL_Quit();
}

int main(int argc, char** argv) {
	SDL_Surface* surface = NULL;
	SDL_Window* window = NULL;
	bool quit = false;
	Uint8 red = 0;
	SDL_Event e;

	window = initSDL();

	// Handle test drawing
	surface = SDL_GetWindowSurface(window);

	// Wait for quit command from user
	while(quit == false) {
		// User input
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				quit = true;
		}

		red++;

		// Game logic

		// Drawing logic
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, red, 0, 0));
		SDL_UpdateWindowSurface(window);
	}

	quitSDL(window);

	return 0;
}