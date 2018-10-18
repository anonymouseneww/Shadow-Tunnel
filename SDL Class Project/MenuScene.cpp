#include "MenuScene.h"



MenuScene::MenuScene() {
	// Add title image
	backgroundRect = { 0, 0, 1600, 900 };
	backgroundTexture = IMG_LoadTexture(Globals::renderer, "Assets/Menu_Background_2.png");
	//titleRect = { 40, 100, 1000, 100 };
	//titleTexture = IMG_LoadTexture(renderer, "Assets/Shadow_Tunnel_Title_2.png");

	// Button default is (350 * 70), But it also takes two params Button(w, h);
	playButton = new Button(400, 70);
	playButton->setRenderer(Globals::renderer);
	playButton->pos.x = 40;
	playButton->pos.y = 670;

	menuObjects.push_back(playButton);

	exitButton = new Button(400, 70);
	exitButton->setRenderer(Globals::renderer);
	exitButton->pos.x = 40;
	exitButton->pos.y = 760;

	menuObjects.push_back(exitButton);

	// Add title
	TTF_Font *titleFont = TTF_OpenFont("Assets/Roboto/RobotoCondensed-Bold.ttf", 120);
	// Create a color for our text
	SDL_Color titleTextColour = { 220, 220, 220, 0 }; // RGBA
		// Create surface using font , colour and desired output text
	SDL_Surface *titleTextSurface = TTF_RenderText_Blended(titleFont, "SHADOW TUNNEL", titleTextColour);
	// Conver Surgace to texture
	titleTexture = SDL_CreateTextureFromSurface(Globals::renderer, titleTextSurface);
	// DOn;t need the surface no more
	SDL_FreeSurface(titleTextSurface);

	// Setup rectangle to describe where to draw this text
	titleRect.x = 40;
	titleRect.y = 100;
	// TO get the width and ehight, query the surface
	SDL_QueryTexture(titleTexture, NULL, NULL, &titleRect.w, &titleRect.h);


	// Add play button font
	TTF_Font *playFont = TTF_OpenFont("Assets/Roboto/Roboto-Regular.ttf", 36);
	// Create a color for our text
	SDL_Color playTextColour = { 220, 220, 220, 0 }; // RGBA
		// Create surface using font , colour and desired output text
	SDL_Surface *playTextSurface = TTF_RenderText_Blended(playFont, "Play Game", playTextColour);
	// Conver Surgace to texture
	playButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, playTextSurface);
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
	SDL_Color exitTextColour = { 220, 220, 220, 0 }; // RGBA
		// Create surface using font , colour and desired output text
	SDL_Surface *exitTextSurface = TTF_RenderText_Blended(exitFont, "Exit Game", exitTextColour);
	// Conver Surgace to texture
	exitButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, exitTextSurface);
	// DOn;t need the surface no more
	SDL_FreeSurface(exitTextSurface);

	// Setup rectangle to describe where to draw this text
	exitButtonRect.x = 70;
	exitButtonRect.y = 775;
	// TO get the width and ehight, query the surface
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonRect.w, &exitButtonRect.h);

	// Input Handlers
	mouseHandler = new MouseHandler();
}

MenuScene::~MenuScene() {
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(playButtonTexture);
	SDL_DestroyTexture(exitButtonTexture);
	SDL_DestroyTexture(incompleteButtonTexture);
}


void MenuScene::update() {
	// Check for input
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Check if the window is closed
		if (event.type == SDL_QUIT) {
			Globals::quitGame = true;
			return;
		}

		// Exit game when "Esc" is pressed
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				Globals::quitGame = true;
				return;
			}
		}

		// prompt message when click on "Play Game"
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			// But was it clicked within hero region?
			if (event.button.x >= playButton->pos.x && event.button.x <= playButton->pos.x + 400
				&&
				event.button.y >= playButton->pos.y && event.button.y <= playButton->pos.y + 70) {
				// Switch to "PlayGame" Scene
			}
		}

		// Exit game when clicked "Exit Game" button
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			// But was it clicked within hero region?
			if (event.button.x >= exitButton->pos.x && event.button.x <= exitButton->pos.x + 400
				&&
				event.button.y >= exitButton->pos.y && event.button.y <= exitButton->pos.y + 70) {
				Globals::quitGame = true;
				return;
			}
		}
	}


	// Monitor Mouse Coordinate
	mousePos = mouseHandler->getMouseState();
	cout << "  Mouse Coordinate (" << mousePos.x << ", " << mousePos.y << ")\n";

	

}

void MenuScene::render() {
	// Render Background
	SDL_RenderCopy(Globals::renderer, backgroundTexture, NULL, &backgroundRect);

	// Draw each menu objects
	for (GameObject *mo : menuObjects) {
		mo->draw(mo->checkIfHover(mousePos));
	}

	// Render textTexture
	//SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(Globals::renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(Globals::renderer, playButtonTexture, NULL, &playButtonRect);
	SDL_RenderCopy(Globals::renderer, exitButtonTexture, NULL, &exitButtonRect);

	// Present all our renderings to the window when you have enough drawing stuffs
	SDL_RenderPresent(Globals::renderer);
}

bool MenuScene::onEnter() {
	cout << "Entered Menu Scene" << endl;
	return true;

}
bool MenuScene::onExit() {
	cout << "Exiting Menu Scene" << endl;
	return true;
}
