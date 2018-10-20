#pragma once
#include "GameObject.h"
#include "Animation.h"

class Player :
	public GameObject
{
public:
	Player();
	~Player();

	void setAnimation(Animation *animation);
	virtual void update(float dt);
	virtual void draw();

private:
	Animation *animation = NULL;
	bool faceRight = true;
	bool faceUp = true;
};

