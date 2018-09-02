#pragma once
#include "GameObject.h"

class MenuScene : public GameObject {
public:
	MenuScene();
	~MenuScene();

	virtual void draw();

private:
	int w, h;

};