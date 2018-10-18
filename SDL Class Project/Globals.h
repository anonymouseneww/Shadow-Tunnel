#pragma once
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GameSceneManager.h"
#include "MouseHandler.h"

class Globals
{
public:
	Globals();
	~Globals();

	float calculateDeltaTime();

	// Setup Basic stuffs
	static SDL_Renderer *renderer;
	static bool quitGame;
	static GameSceneManager gsm;
	float deltaTime = calculateDeltaTime();

	// Setup inputHandlers

	// Setup Stuffs for the game
	
private:
	// Prep time stuff
	Uint32 lastUpdate = SDL_GetTicks(); // Milliseconds since the start of the game running
};

