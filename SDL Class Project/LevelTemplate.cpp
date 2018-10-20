#include "LevelTemplate.h"

LevelTemplate::LevelTemplate() {

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
	mousePos = mouseHandler->getMouseState();
	//cout << "  Mouse Coordinate (" << mousePos.x << ", " << mousePos.y << ")\n";



}

void LevelTemplate::render() {
	// Render Background
	//SDL_RenderCopy(Globals::renderer, backgroundTexture, NULL, &backgroundRect);


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