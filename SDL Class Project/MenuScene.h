#pragma once
#include <list>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Globals.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Button.h"

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
		return "playState";
	}

private:
	Button *playButton, *exitButton, *okayButton;

	SDL_Texture *backgroundTexture, *titleTexture, *playButtonTexture, *exitButtonTexture, *incompleteButtonTexture;
	SDL_Rect backgroundRect, titleRect, playButtonRect, exitButtonRect, incompleteRect, incompleteButtonRect;

	// List of stuffs to render;
	list<GameObject*> menuObjects;

	// Input Handler for MenuScene
	MouseHandler *mouseHandler;
	Vector mousePos;

};