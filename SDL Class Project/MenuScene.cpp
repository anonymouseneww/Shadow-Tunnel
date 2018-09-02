#include "MenuScene.h"



MenuScene::MenuScene() {
	this->w = 100;
	this->h = 30;
}


MenuScene::~MenuScene() {

}


void MenuScene::draw() {
	SDL_Rect button = { pos.x, pos.y, w, h };
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderFillRect(renderer, &button);

}
