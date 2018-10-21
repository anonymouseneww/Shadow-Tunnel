#include "LevelSelection.h"

LevelSelection::LevelSelection() {
	// Add title image
	backgroundRect = { 0, 0, 1600, 900 };
	backgroundTexture = IMG_LoadTexture(Globals::renderer, "Assets/Menu_Background_2.png");
	
	// Button default is (37 * 50), But it also takes two params Button(w, h);
	lvl1Button = new Button();
	lvl1Button->setRenderer(Globals::renderer);
	lvl1Button->pos.x = 40;
	lvl1Button->pos.y = 565;

	renderObjects.push_back(lvl1Button);

	lvl2Button = new Button();
	lvl2Button->setRenderer(Globals::renderer);
	lvl2Button->pos.x = 40;
	lvl2Button->pos.y = 640;

	renderObjects.push_back(lvl2Button);

	lvl3Button = new Button();
	lvl3Button->setRenderer(Globals::renderer);
	lvl3Button->pos.x = 40;
	lvl3Button->pos.y = 715;

	renderObjects.push_back(lvl3Button);

	backButton = new Button();
	backButton->setRenderer(Globals::renderer);
	backButton->pos.x = 40;
	backButton->pos.y = 790;

	renderObjects.push_back(backButton);

	// Setup the font and font color
	font = TTF_OpenFont("Assets/Roboto/Roboto-Regular.ttf", 32);
	fontColor = { 220, 220, 220, 0 }; // RGBA

	// Add title --------------------------------------------------------------------------------------------------------------------------------------------------------
	TTF_Font *titleFont = TTF_OpenFont("Assets/Roboto/Roboto-Regular.ttf", 80);
	SDL_Surface *titleTextSurface = TTF_RenderText_Blended(titleFont, "> Select Level", fontColor);
	titleTexture = SDL_CreateTextureFromSurface(Globals::renderer, titleTextSurface);
	SDL_FreeSurface(titleTextSurface);

	titleRect.x = 40;
	titleRect.y = 40;
	SDL_QueryTexture(titleTexture, NULL, NULL, &titleRect.w, &titleRect.h);


	// Add Level 1 button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *lvl1TextSurface = TTF_RenderText_Blended(font, "Level 1", fontColor);
	lvl1ButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, lvl1TextSurface);
	SDL_FreeSurface(lvl1TextSurface);

	lvl1ButtonRect.x = 70;
	lvl1ButtonRect.y = 575;
	SDL_QueryTexture(lvl1ButtonTexture, NULL, NULL, &lvl1ButtonRect.w, &lvl1ButtonRect.h);


	// Add Level 2 button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *lvl2TextSurface = TTF_RenderText_Blended(font, "Level 2", fontColor);
	lvl2ButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, lvl2TextSurface);
	SDL_FreeSurface(lvl2TextSurface);

	lvl2ButtonRect.x = 70;
	lvl2ButtonRect.y = 650;
	SDL_QueryTexture(lvl2ButtonTexture, NULL, NULL, &lvl2ButtonRect.w, &lvl2ButtonRect.h);


	// Add Level 3 button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *lvl3TextSurface = TTF_RenderText_Blended(font, "Level 3", fontColor);
	lvl3ButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, lvl3TextSurface);
	SDL_FreeSurface(lvl3TextSurface);

	lvl3ButtonRect.x = 70;
	lvl3ButtonRect.y = 725;
	SDL_QueryTexture(lvl3ButtonTexture, NULL, NULL, &lvl3ButtonRect.w, &lvl3ButtonRect.h);


	// Add back button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *exitTextSurface = TTF_RenderText_Blended(font, "Back to Menu", fontColor);
	backButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, exitTextSurface);
	SDL_FreeSurface(exitTextSurface);

	backButtonRect.x = 70;
	backButtonRect.y = 800;
	SDL_QueryTexture(backButtonTexture, NULL, NULL, &backButtonRect.w, &backButtonRect.h);

	// Input Handlers
	mouseHandler = new MouseHandler();
}

LevelSelection::~LevelSelection() {
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(lvl1ButtonTexture);
	SDL_DestroyTexture(lvl2ButtonTexture);
	SDL_DestroyTexture(lvl3ButtonTexture);
	SDL_DestroyTexture(backButtonTexture);
}


void LevelSelection::update() {
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

		// Switch to Level 1 when button is pressed
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= lvl1Button->pos.x && event.button.x <= lvl1Button->pos.x + 400
				&&
				event.button.y >= lvl1Button->pos.y && event.button.y <= lvl1Button->pos.y + 70) {
				// Switch to "Level1" Scene
				// Testing Purpose
				Globals::gsm.pushScene(new LevelTemplate());
			}
		}

		// Switch to Level 2 when button is pressed
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= lvl2Button->pos.x && event.button.x <= lvl2Button->pos.x + 400
				&&
				event.button.y >= lvl2Button->pos.y && event.button.y <= lvl2Button->pos.y + 70) {
				// Switch to "Level2" Scene
			}
		}

		// Switch to Level 3 when button is pressed
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= lvl3Button->pos.x && event.button.x <= lvl3Button->pos.x + 400
				&&
				event.button.y >= lvl3Button->pos.y && event.button.y <= lvl3Button->pos.y + 70) {
				// Switch to "Level3" Scene
			}
		}

		// Exit game when clicked "Exit Game" button
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= backButton->pos.x && event.button.x <= backButton->pos.x + 400
				&&
				event.button.y >= backButton->pos.y && event.button.y <= backButton->pos.y + 70) {
				Globals::gsm.popScene();
				return;
			}
		}
	}


	// Monitor Mouse Coordinate
	mousePos = mouseHandler->getMouseState();
	//cout << "  Mouse Coordinate (" << mousePos.x << ", " << mousePos.y << ")\n";



}

void LevelSelection::render() {
	// Render Background
	SDL_RenderCopy(Globals::renderer, backgroundTexture, NULL, &backgroundRect);

	// Draw each menu objects
	for (GameObject *ro : renderObjects) {
		ro->draw(ro->checkIfHover(mousePos));
	}

	// Render textTexture
	//SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(Globals::renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(Globals::renderer, lvl1ButtonTexture, NULL, &lvl1ButtonRect);
	SDL_RenderCopy(Globals::renderer, lvl2ButtonTexture, NULL, &lvl2ButtonRect);
	SDL_RenderCopy(Globals::renderer, lvl3ButtonTexture, NULL, &lvl3ButtonRect);
	SDL_RenderCopy(Globals::renderer, backButtonTexture, NULL, &backButtonRect);

	// Present all our renderings to the window when you have enough drawing stuffs
	SDL_RenderPresent(Globals::renderer);
}

bool LevelSelection::onEnter() {
	cout << "Pushed Level Selection Scene" << endl;
	return true;
}

bool LevelSelection::onExit() {
	cout << "Popped Level Selection Scene" << endl;
	return true;
}
