#include <iostream>
#include <string>
#include <list>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "Button.h"

using namespace std;

float calculateDeltaTime(Uint32 &);
void checkInput();
void updateMenu(list<GameObject*>, float);

int main(int argc, char **argv){
	// Initialise SDL with all the subsystem coz im lazy
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL failed to initialise" << endl;
		return -1;
	}
	cout << "SDL successfully initialised!" << endl;

	// Create window to render stuffs
	// Resolution: 1920 * 1080
	// Screen Mode: Windowed
	SDL_Window* window = SDL_CreateWindow("Shadow Tunnel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 768, SDL_WINDOW_SHOWN); //for full screen use SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN

	// Check if window work
	if (window != NULL)
		cout << "Window created!" << endl;
	else
	{
		cout << "Window failed!" << endl;
		return -1;
	}

	// Create renderer to ummm draw stuffs
		//params: window to create renderer for, render driver index(-1, get first best match), flags for what renderer can handle
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//did it work?
	if (renderer != NULL){
		cout << "renderer created!" << endl;
	}
	else
	{
		cout << "renderer failed!" << endl;
		return -1;
	}

	// Set drawing color for renderer to draw background color
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);





	// List of stuffs to render;
	list<GameObject*> menuObjects;
	
	// Build Title
	int w = 200;
	int h = 100;
	//SDL_Texture *titleTexture = IMG_LoadTexture(renderer, "Assets\Shadow_Tunnel_Title_1.png");
	//SDL_QueryTexture(titleTexture, NULL, NULL, &w, &h);

	//SDL_Rect titleRect = { 400, 400, w, h};


	// Create a stuffs here
	Button *button1 = new Button();
	button1->setRenderer(renderer);
	button1->pos.x = 40;
	button1->pos.y = 40;

	menuObjects.push_back(button1);

	// Prep time stuff
	Uint32 lastUpdate = SDL_GetTicks(); // Milliseconds since the start of the game running

	// Current frame (0-3)
	int currentFrame = 0;
	float frameTimer = 0.083;

	bool loop = true;
	while (loop) {
		// Time stuffs (This is for people with fast computers (Like me))
		float deltaTime = calculateDeltaTime(lastUpdate);

		// Check for input
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// Check if the window is closed
			if (event.type == SDL_QUIT) {
				loop = false;
			}

			// Exit game when "Esc" is pressed
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					loop = false;
				}
			}
		}


		// Run updateMenu Function (Useless Comment)
		updateMenu(menuObjects, deltaTime);

		//SDL_RenderClear(renderer);
		//SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

		// Present all our renderings to the window when you have enough drawing stuffs
		SDL_RenderPresent(renderer);
		
	}

	
	//cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//shut down sdl sub systems
	SDL_Quit();

	return 0;
}

// Calculate then return DeltaTime
float calculateDeltaTime(Uint32 &lastUpdate) {
	// Get difference between currentTime and lastUpdate Time
	Uint32 timeDiff = SDL_GetTicks() - lastUpdate;

	// Convert to DeltaTime
	float dt = timeDiff / 1000.0; // Conver dt ms to dt s
								  // Update lastUpdate
	lastUpdate = SDL_GetTicks();
	// Output DeltaTime
	cout << "  dt = " << dt << endl;
	
	return dt;
}


// Update stuffs in menuObjects list
void updateMenu(list<GameObject*> _menuObjects, float _dt) {
	for (GameObject *mo : _menuObjects) {
		mo->update(_dt);
		mo->draw();
	}
}