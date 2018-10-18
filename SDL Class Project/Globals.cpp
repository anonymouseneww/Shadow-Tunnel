#include "Globals.h"


Globals::Globals() {}
Globals::~Globals() {}

float Globals::calculateDeltaTime() {
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

SDL_Renderer *Globals::renderer = NULL;
bool Globals::quitGame = false;
GameSceneManager Globals::gsm;