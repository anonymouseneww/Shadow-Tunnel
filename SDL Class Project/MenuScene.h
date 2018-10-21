#pragma once
#include <list>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Globals.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Button.h"

#include "LevelSelection.h"
#include "LeaderboardScene.h"

class MenuScene : public GameScene {
public:
	MenuScene();
	~MenuScene();

	//override those abstract methods inherited from GameScene
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() {
		return "MenuScene";
	}

private:
	Button *playButton, *leaderboardButton, *exitButton;

	TTF_Font *font;
	SDL_Color fontColor;

	SDL_Texture *backgroundTexture, *titleTexture, *playButtonTexture, *leaderboardButtonTexture, *exitButtonTexture;
	SDL_Rect backgroundRect, titleRect, playButtonRect, leaderboardButtonRect, exitButtonRect;

	// List of stuffs to render;
	list<GameObject*> renderObjects;

	// Input Handler for MenuScene
	MouseHandler *mouseHandler;
	Vector mousePos;

};