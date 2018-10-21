#include "MenuScene.h"

MenuScene::MenuScene() {
	// Add title image
	backgroundRect = { 0, 0, 1600, 900 };
	backgroundTexture = IMG_LoadTexture(Globals::renderer, "Assets/Menu_Background_2.png");

	// Button default is (370 * 50), But it also takes two params Button(w, h);
	playButton = new Button();
	playButton->setRenderer(Globals::renderer);
	playButton->pos.x = 40;
	playButton->pos.y = 640;

	renderObjects.push_back(playButton);

	leaderboardButton = new Button();
	leaderboardButton->setRenderer(Globals::renderer);
	leaderboardButton->pos.x = 40;
	leaderboardButton->pos.y = 715;

	renderObjects.push_back(leaderboardButton);

	exitButton = new Button();
	exitButton->setRenderer(Globals::renderer);
	exitButton->pos.x = 40;
	exitButton->pos.y = 790;

	renderObjects.push_back(exitButton);

	// Setup the font and font color
	font = TTF_OpenFont("Assets/Roboto/Roboto-Regular.ttf", 32);
	fontColor = { 220, 220, 220, 0 }; // RGBA

	// Add title --------------------------------------------------------------------------------------------------------------------------------------------------------
	TTF_Font *titleFont = TTF_OpenFont("Assets/Roboto/Roboto-Bold.ttf", 100);
	SDL_Surface *titleTextSurface = TTF_RenderText_Blended(titleFont, "SHADOW TUNNEL", fontColor);
	titleTexture = SDL_CreateTextureFromSurface(Globals::renderer, titleTextSurface);
	SDL_FreeSurface(titleTextSurface);

	titleRect.x = 40;
	titleRect.y = 40;
	SDL_QueryTexture(titleTexture, NULL, NULL, &titleRect.w, &titleRect.h);

	
	// Add play button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *playTextSurface = TTF_RenderText_Blended(font, "Play Game", fontColor);
	playButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, playTextSurface);
	SDL_FreeSurface(playTextSurface);

	playButtonRect.x = 70;
	playButtonRect.y = 650;
	SDL_QueryTexture(playButtonTexture, NULL, NULL, &playButtonRect.w, &playButtonRect.h);

	
	// Add leaderboard button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *leaderboardTextSurface = TTF_RenderText_Blended(font, "Leaderboard", fontColor);
	leaderboardButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, leaderboardTextSurface);
	SDL_FreeSurface(leaderboardTextSurface);

	leaderboardButtonRect.x = 70;
	leaderboardButtonRect.y = 725;
	SDL_QueryTexture(leaderboardButtonTexture, NULL, NULL, &leaderboardButtonRect.w, &leaderboardButtonRect.h);


	// Add exit button font --------------------------------------------------------------------------------------------------------------------------------------------------------
	SDL_Surface *exitTextSurface = TTF_RenderText_Blended(font, "Exit Game", fontColor);
	exitButtonTexture = SDL_CreateTextureFromSurface(Globals::renderer, exitTextSurface);
	SDL_FreeSurface(exitTextSurface);

	exitButtonRect.x = 70;
	exitButtonRect.y = 800;
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonRect.w, &exitButtonRect.h);

	// Input Handlers
	mouseHandler = new MouseHandler();
}

MenuScene::~MenuScene() {
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(playButtonTexture);
	SDL_DestroyTexture(leaderboardButtonTexture);
	SDL_DestroyTexture(exitButtonTexture);
}


void MenuScene::update() {
	// Check for input
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Check if the window is closed
		if (event.type == SDL_QUIT) {
			Globals::quitGame = true;
			Globals::gsm.popScene();
			return;
		}

		// Exit game when "Esc" is pressed
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				Globals::quitGame = true;
				Globals::gsm.popScene();
				return;
			}
		}

		// Switch to Level Selection when button is pressed
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= playButton->pos.x && event.button.x <= playButton->pos.x + 320
				&&
				event.button.y >= playButton->pos.y && event.button.y <= playButton->pos.y + 60) {
				// Switch to "Level Selection" Scene
				Globals::gsm.pushScene(new LevelSelection());
			}
		}
		
		// Switch to Leaderboard Scene when button is pressed
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= leaderboardButton->pos.x && event.button.x <= leaderboardButton->pos.x + 320
				&&
				event.button.y >= leaderboardButton->pos.y && event.button.y <= leaderboardButton->pos.y + 60) {
				// Switch to "Leaderboard" Scene
				Globals::gsm.pushScene(new LeaderboardScene());
			}
		}

		// Exit game when clicked "Exit Game" button
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			if (event.button.x >= exitButton->pos.x && event.button.x <= exitButton->pos.x + 320
				&&
				event.button.y >= exitButton->pos.y && event.button.y <= exitButton->pos.y + 60) {
				Globals::quitGame = true;
				Globals::gsm.popScene();
				return;
			}
		}
	}
	
	// Monitor Mouse Coordinate
	mousePos = mouseHandler->getMouseState();
	//cout << "  Mouse Coordinate (" << mousePos.x << ", " << mousePos.y << ")\n";
}

void MenuScene::render() {
	// Render Background
	SDL_RenderCopy(Globals::renderer, backgroundTexture, NULL, &backgroundRect);

	// Draw each menu objects
	for (GameObject *ro : renderObjects) {
		ro->draw(ro->checkIfHover(mousePos));
	}

	// Render textTexture
	//SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(Globals::renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(Globals::renderer, playButtonTexture, NULL, &playButtonRect);
	SDL_RenderCopy(Globals::renderer, leaderboardButtonTexture, NULL, &leaderboardButtonRect);
	SDL_RenderCopy(Globals::renderer, exitButtonTexture, NULL, &exitButtonRect);

	// Present all our renderings to the window when you have enough drawing stuffs
	SDL_RenderPresent(Globals::renderer);
}

bool MenuScene::onEnter() {
	cout << "Pushed Menu Scene" << endl;
	return true;
}

bool MenuScene::onExit() {
	cout << "Popped Menu Scene" << endl;
	return true;
}
