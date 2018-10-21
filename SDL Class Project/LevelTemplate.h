#pragma once
#include <list>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Globals.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Button.h"

class LevelTemplate : public GameScene {
public:
	LevelTemplate();
	~LevelTemplate();

	//override those abstract methods inherited from GameScene
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() { return "LevelTemplate"; }

private:
<<<<<<< HEAD
	SDL_Rect backgroundRect;

=======
>>>>>>> f72dddcceebaa5d641626acc35221fe5d3ae6b98
	// List of stuffs to render;
	list<GameObject*> renderObjects;

	// Input Handler for MenuScene
	MouseHandler *mouseHandler;
	Vector mousePos;

};