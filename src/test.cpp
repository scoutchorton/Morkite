#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 30 // Frames Per Second
#define TPF 1000 / FPS // Ticks Per Frame

/*
Resources

SDL Tutorials: https://lazyfoo.net/tutorials/SDL/index.php
*/

// Globals
/** @todo remove later */
SDL_Window* window = NULL;

int setWindowTitle_L(lua_State*);

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

lua_State* initLua() {
	lua_State* Lua = luaL_newstate();
	luaL_openlibs(Lua);

	lua_pushcfunction(Lua, setWindowTitle_L);
	lua_setglobal(Lua, "setWindowTitle");

	return Lua;
}

int setWindowTitle_L(lua_State* Lua) {
	const char* windowNameArg = NULL;
	//std::string windowName;

	// Get the new name and convert to C++ string
	windowNameArg = lua_tolstring(Lua, 1, NULL);
	//windowName = windowNameArg;
	SDL_SetWindowTitle(window, windowNameArg);

	// Lua return thing
	lua_pushnil(Lua);

	return 1;
}

int main(int argc, char** argv) {
	lua_State* Lua;
	SDL_Surface* surface = NULL;
	SDL_Surface* spriteSheet = NULL;
	SDL_Rect spriteSheetClip[6];
	SDL_Rect centerRect;
	bool quit = false;
	Uint8 red = 0;
	SDL_Event e;

	int hasRunLua = 0;
	int animationFrame = 0;

	// Initialization
	window = initSDL();
	Lua = initLua();

	// Handle test drawing
	surface = SDL_GetWindowSurface(window);

	// Load in the sprite data
	spriteSheet = IMG_Load("./assets/test_character/walk_transparent.png");
	for(int i = 0; i < 6; i++) {
		spriteSheetClip[i] = {
			.x = (i * 300), .y = 0,
			.w = 300, .h = 300
		};
	}

	centerRect = {
		.x = (SCREEN_WIDTH / 2) - (300 / 2), .y = (SCREEN_HEIGHT / 2) - (300 / 2),
		.w = SCREEN_WIDTH, .h = SCREEN_HEIGHT
	};

	//luaL_dofile(Lua, "./src/test.lua");

	// Wait for quit command from user
	while(quit == false) {
		// User input
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				quit = true;
		}

		red++;
		hasRunLua++;
		animationFrame++;

		// Game logic
		if(hasRunLua == 255/4)
			luaL_dofile(Lua, "./src/test.lua");

		// Drawing logic
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, red, 0, 0));
		SDL_BlitSurface(spriteSheet, &spriteSheetClip[animationFrame % 3 + 3], surface, &centerRect);
		SDL_UpdateWindowSurface(window);

		SDL_Delay(100);
	}

	quitSDL(window);

	return 0;
}