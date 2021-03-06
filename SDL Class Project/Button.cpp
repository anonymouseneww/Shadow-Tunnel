#include "Button.h"
#include <iostream>

Button::Button() {
	this->w = 350;
	this->h = 70;
}

Button::Button(int _w, int _h) {
	this->w = _w;
	this->h = _h;
}


Button::~Button() {

}

void Button::draw(bool _ifHover) {
	SDL_Rect button = { pos.x, pos.y, w, h };

	if (_ifHover) {
		SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
		SDL_RenderFillRect(renderer, &button);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
		SDL_RenderFillRect(renderer, &button);
	}

}

// Check if the mouse is over the button
bool Button::checkIfHover(Vector _MousePos) {
	if (_MousePos.x > pos.x && _MousePos.x < (pos.x + w) && _MousePos.y > pos.y && _MousePos.y < (pos.y + h)) {
		cout << "  Mouse in the box!!\n";
		return true;
	}
	else {
		return false;
	}

}