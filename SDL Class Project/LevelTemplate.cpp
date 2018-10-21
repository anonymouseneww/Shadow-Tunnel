#include "LevelTemplate.h"

LevelTemplate::LevelTemplate() {
<<<<<<< HEAD
	// Setup level background
	backgroundRect = {1600, 900, 0, 0};

=======
	// Set the background to black
>>>>>>> f72dddcceebaa5d641626acc35221fe5d3ae6b98
}

LevelTemplate::~LevelTemplate() {
}


void LevelTemplate::update() {
	// Check for input
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Check if the window is closed
		if (event.type == SDL_QUIT) {
			Globals::quitGame = true;
			return;
		}
	}


	// Monitor Mouse Coordinate
	//mousePos = mouseHandler->getMouseState();
}

void LevelTemplate::render() {
	// Render Background
	//SDL_RenderCopy(Globals::renderer, backgroundTexture, NULL, &backgroundRect);

	SDL_SetRenderDrawColor(Globals::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Globals::renderer);

	// Present all our renderings to the window when you have enough drawing stuffs
	SDL_RenderPresent(Globals::renderer);
}

bool LevelTemplate::onEnter() {
	cout << "Pushed Level Template Scene" << endl;
	return true;
}

bool LevelTemplate::onExit() {
	cout << "Popped Level Template Scene" << endl;
	return true;
}
