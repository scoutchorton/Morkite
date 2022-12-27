#include <iostream>

#include <SDL2/SDL.h>
#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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
	//lua_pushnil(Lua);

	return 0;
}

int main(int argc, char** argv) {
	lua_State* Lua;
	SDL_Surface* surface = NULL;
	bool quit = false;
	Uint8 red = 0;
	SDL_Event e;

	int hasRunLua = 0;

	// Initialization
	window = initSDL();
	Lua = initLua();

	// Handle test drawing
	surface = SDL_GetWindowSurface(window);

	luaL_dofile(Lua, "./src/test.lua");

	// Wait for quit command from user
	while(quit == false) {
		// User input
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				quit = true;
		}

		red++;
		hasRunLua++;

		// Game logic
		if(hasRunLua == 100000)
			luaL_dofile(Lua, "./src/test.lua");

		// Drawing logic
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, red, 0, 0));
		SDL_UpdateWindowSurface(window);
	}

	quitSDL(window);

	return 0;
}