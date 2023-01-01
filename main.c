#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#define SDL_MAIN_HANDLED
// This configuration breaks the intended method of SDL package.
						 // OLDER COMMENTS!
						 //This fixes the error that causes `int main(int argc,
						 //char const *argv[])` conflicting with `int
						 //SDL_MAIN(int argc, char const *argv[])` in WINDOWS
						 //PLATFORM.
						 // This (#define SDL_MAIN_HANDLED)should be delcared
						 // before including `SDL.H`
						 //
						 // Only problem is that we have to define manual entry
						 // point to the start of our code by calling the 
						 // function `SDL_SetMainReady()` in the `main(int
						 // argc, char const *argv[])`
						 //
// Without doing all of this, just change the input patemeters of the main
// function to `int main(int argc, char *argv[])` as suggested in the SDL
// Library.
#include <SDL.h>
#include "font.h"

void scc(int code) {
	if (code < 0) {
		fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
		exit(1);
	}
}

// scp - secured content protect
void *scp(void *ptr) {
	if (ptr == NULL) {
		fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
		exit(1);
	}

	return ptr;
}

int main(int argc, char *argv[]) {
	// Stop the `unused parameter warning :
	// This tells the compiler to use but never do anything with it
	// sort of ... `(void)variable_name`
	//
	// When using `-Wall -pedantic -Wextra` flag, unused variable halts the 
	// compiler
	// CREDIT: John's Basement YouTube channel
	(void)argc;
	(void)argv;


// No requirement of the SDL_SetMainReady() as the method we used for writing
// different type of main function with different input parameters is not at
// all intended by library itself.
//	SDL_SetMainReady();	
//						// OLDER COMMENTS
						// Calling this because of WINDOWS PLATFORM issue
						// discussed while including SDL2 in header section.
						//
						// or do the setting given in the define of this file
						// at the very last of the comments.
	scc(SDL_Init(SDL_INIT_VIDEO));

	SDL_Window * window = scp(SDL_CreateWindow(
							"Program",
							0, 0,
							800, 600,
							SDL_WINDOW_RESIZABLE));
	SDL_Renderer * renderer = 
		scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

	SDL_Surface * surface = scp(SDL_CreateRGBSurfaceFrom(FONT,
				FONT_WIDTH,
				FONT_HEIGHT,
				8,
				FONT_WIDTH,
				0xFF, 
				0xFF, 
				0xFF, 
				0xFF));

	SDL_Texture * texture =
		scp(SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_INDEX8,
			SDL_TEXTUREACCESS_STATIC,
			FONT_WIDTH,
			FONT_HEIGHT));

	bool quit = false;
	while (!quit) {
		SDL_Event event = {0};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					quit = true;
				} break;
			}
		}
		
		scc(SDL_SetRenderDrawColor(renderer, 100, 0, 0, 0));
		scc(SDL_RenderClear(renderer));
		
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}
