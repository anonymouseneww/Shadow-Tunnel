#pragma once
#include "GameObject.h"

class Button : public GameObject
{
public:
	Button();
	~Button();

	virtual void draw();

private:
	int w, h;

};

