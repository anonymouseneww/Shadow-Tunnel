#include <iostream>
#include <string>
#include <list>
#include <windows.h>


#include "Globals.h"
#include "MenuScene.h"

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;

int initializeSDL() {
	// Initialise SDL with all the subsystem coz im lazy
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL failed to initialise" << endl;
		return -1;
	}

	cout << "SDL successfully initialised!" << endl;

	// Initialize SDL_ttf
	if (TTF_Init() != 0) {
		//if failed, complain about it
		cout << "SDL TTF FAILED!" << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}

	// Initialize SDL_image 
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		cout << "sdl image did not load: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	// Create window to render stuffs
	// Resolution: 1600 * 900
	// Screen Mode: Windowed
	window = SDL_CreateWindow("Shadow Tunnel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1600, 900, SDL_WINDOW_SHOWN); //for full screen use SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN

	// Check if window work
	if (window != NULL)
		cout << "Window created!" << endl;
	else { 
		cout << "Window failed!" << endl;
		return -1;
	}

	// Create renderer to ummm draw stuffs
		//params: window to create renderer for, render driver index(-1, get first best match), flags for what renderer can handle
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//did it work?
	if (renderer != NULL) {
		cout << "renderer created!" << endl;
	} else {
		cout << "renderer failed!" << endl;
		return -1;
	}

	// Point Global renderer to our renderer
	Globals::renderer = renderer;

	// Set drawing color for renderer to draw background color
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 120);
	SDL_RenderClear(renderer);
}

int main(int argc, char **argv){
	// Initialize SDL System
	initializeSDL();
	
	// Current frame (0-3)
	int currentFrame = 0;
	float frameTimer = 0.083;

	Globals::gsm.pushScene(new MenuScene());

	bool loop = true;
	while (loop) {
		Globals::gsm.update();
		Globals::gsm.render();

		if (Globals::quitGame || Globals::gsm.gameScenes.empty()) {
			loop = false;
		}
	}

	// Cleanup GameSceneManager
	Globals::gsm.clearAll();
	

	// Destroyer Renderer and Window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Shutdwon all SDL systems
	SDL_Quit();
	return 0;
}