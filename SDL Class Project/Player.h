#pragma once

#include <SDL_image.h>

#include "Globals.h"
#include "GameObject.h"
#include "Animation.h"

class Player :
	public GameObject
{
public:
	Player(int, int, int);
	~Player();

	void setAnimation(Animation *animation);
	virtual void update(float dt);
	virtual void draw(bool);

private:
	SDL_Surface *animatedSurface;
	SDL_Texture *playerTexture;

	Animation *animation = NULL;
	bool faceRight = true;
	bool isActive = false;
};

