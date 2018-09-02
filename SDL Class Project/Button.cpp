#include "Button.h"

Button::Button() {
	this->w = 130;
	this->h = 30;
}


Button::~Button() {

}

void Button::draw() {
	SDL_Rect button = { pos.x, pos.y, w, h };
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderFillRect(renderer, &button);

}