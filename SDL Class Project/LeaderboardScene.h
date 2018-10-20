#pragma once
#include <list>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Globals.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Button.h"

class LeaderboardScene : public GameScene {
public:
	LeaderboardScene();
	~LeaderboardScene();

	//override those abstract methods inherited from GameScene
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() {
		return "LeaderboardScene";
	}

private:
	Button *backButton;

	TTF_Font *font;
	SDL_Color fontColor;

	SDL_Texture *backgroundTexture, *titleTexture, *backButtonTexture;
	SDL_Rect backgroundRect, titleRect, backButtonRect;

	// List of stuffs to render;
	list<GameObject*> renderObjects;

	// Input Handler for MenuScene
	MouseHandler *mouseHandler;
	Vector mousePos;

};