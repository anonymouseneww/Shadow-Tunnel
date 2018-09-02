#include <iostream>
#include <string>
#include <list>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GameObject.h"
#include "Button.h"

using namespace std;

// Function Prototypes, just so we don't have a super messy main function
int initializeSDL();
void setupMenu();
float calculateDeltaTime(Uint32 &);
void updateMenu(list<GameObject*>, float, Vector);

// Global Variables - I think this is not a good thing
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	// Menu related
	Button *playButton;
	Button *exitButton;
	
	SDL_Texture *titleTexture, *playButtonTexture, *exitButtonTexture;
	SDL_Rect playButtonRect, exitButtonRect;

	// List of stuffs to render;
	list<GameObject*> menuObjects;

int main(int argc, char **argv){
	// Call initializeSDL Function
	initializeSDL();
	
	// Create the game menu
	setupMenu();

	// Setup Input Handler here for now, coz I need to test it.
	MouseHandler *mH = new MouseHandler();
	
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

		// Monitor Mouse Coordinate
		Vector mousePos = mH->getMouseState();
		cout << "  Mouse Coordinate (" << mousePos.x << ", " << mousePos.y << ")\n";

		// Run updateMenu Function (Useless Comment)
		updateMenu(menuObjects, deltaTime, mousePos);
		
		// Render textTexture
		SDL_RenderCopy(renderer, playButtonTexture, NULL, &playButtonRect);
		SDL_RenderCopy(renderer, exitButtonTexture, NULL, &exitButtonRect);

		// Present all our renderings to the window when you have enough drawing stuffs
		SDL_RenderPresent(renderer);
		
	}

	
	//cleanup
	SDL_DestroyTexture(playButtonTexture);
	SDL_DestroyTexture(exitButtonTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//shut down sdl sub systems
	SDL_Quit();

	return 0;
}

// Initialize SDL and Setup Window
int initializeSDL() {

	// Initialise SDL with all the subsystem coz im lazy
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL failed to initialise" << endl;
		return -1;
	}
	cout << "SDL successfully initialised!" << endl;

	// Create window to render stuffs
	// Resolution: 1600 * 900
	// Screen Mode: Windowed
	window = SDL_CreateWindow("Shadow Tunnel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1600, 900, SDL_WINDOW_SHOWN); //for full screen use SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN

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
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//did it work?
	if (renderer != NULL) {
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

	// Initialize SDL_ttf
	if (TTF_Init() != 0)
	{
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

}

// Add buttons on Menu Scene
void setupMenu() {
	// Button default is (350 * 70), But it also takes two params Button(w, h);
	playButton = new Button(400, 70);
	playButton->setRenderer(renderer);
	playButton->pos.x = 40;
	playButton->pos.y = 670;

	menuObjects.push_back(playButton);

	exitButton = new Button(400, 70);
	exitButton->setRenderer(renderer);
	exitButton->pos.x = 40;
	exitButton->pos.y = 760;

	menuObjects.push_back(exitButton);

	// Add play button font
	TTF_Font *playFont = TTF_OpenFont("Assets/Roboto/Roboto-Regular.ttf", 36);
		// Create a color for our text
	SDL_Color playTextColour = { 255, 255, 255, 0 }; // RGBA
		// Create surface using font , colour and desired output text
	SDL_Surface *playTextSurface = TTF_RenderText_Blended(playFont, "Play Game", playTextColour);
		// Conver Surgace to texture
	playButtonTexture = SDL_CreateTextureFromSurface(renderer, playTextSurface);
		// DOn;t need the surface no more
	SDL_FreeSurface(playTextSurface);

		// Setup rectangle to describe where to draw this text
	playButtonRect.x = 70;
	playButtonRect.y = 685;
		// TO get the width and ehight, query the surface
	SDL_QueryTexture(playButtonTexture, NULL, NULL, &playButtonRect.w, &playButtonRect.h);

	// Add exit button font
	TTF_Font *exitFont = TTF_OpenFont("Assets/Roboto/Roboto-Regular.ttf", 36);
	// Create a color for our text
	SDL_Color exitTextColour = { 255, 255, 255, 0 }; // RGBA
		// Create surface using font , colour and desired output text
	SDL_Surface *exitTextSurface = TTF_RenderText_Blended(exitFont, "Exit Game", exitTextColour);
	// Conver Surgace to texture
	exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitTextSurface);
	// DOn;t need the surface no more
	SDL_FreeSurface(exitTextSurface);

	// Setup rectangle to describe where to draw this text
	exitButtonRect.x = 70;
	exitButtonRect.y = 775;
	// TO get the width and ehight, query the surface
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonRect.w, &exitButtonRect.h);

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
void updateMenu(list<GameObject*> _menuObjects, float _dt, Vector _mousePos) {
	for (GameObject *mo : _menuObjects) {
		mo->update(_dt);
		mo->draw(mo->checkIfHover(_mousePos));
	}
}