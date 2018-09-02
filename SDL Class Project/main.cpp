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
float calculateDeltaTime(Uint32 &);
void checkInput();
void updateMenu(list<GameObject*>, float, Vector);

int main(int argc, char **argv){
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
	SDL_Window* window = SDL_CreateWindow("Shadow Tunnel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
	// Buttom default is (350 * 70), But it also takes two params Button(w, h);
	Button *play = new Button(400, 70);
	play->setRenderer(renderer);
	play->pos.x = 40;
	play->pos.y = 670;

	menuObjects.push_back(play);

	Button *exit = new Button(400, 70);
	exit->setRenderer(renderer);
	exit->pos.x = 40;
	exit->pos.y = 760;

	menuObjects.push_back(exit);
	
	// Setup Input Handler here for now, coz I need to test it.
	MouseHandler *mH = new MouseHandler();


	// Add font
	TTF_Font *font = TTF_OpenFont("Assets/Roboto-Black.ttf", 16);
	// Create a color for our text
	SDL_Color textColour = { 0,0,0, 255 }; // RGBA
	// Create surface using font , colour and desired output text
	SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Play Game", textColour);
	// Conver Surgace to texture
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	// DOn;t need the surface no more
	SDL_FreeSurface(textSurface);

	// Setup rectangle to describe where to draw this text
	SDL_Rect textDestination;
	textDestination.x = 40;
	textDestination.y = 670;
	// TO get the width and ehight, query the surface
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);


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
		SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);

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

// Add buttons on Menu Scene



// Add Font then link it with button
void addFont() {

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