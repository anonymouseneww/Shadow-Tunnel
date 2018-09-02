#include "GameObject.h"

void GameObject::setRenderer(SDL_Renderer* _renderer) {
	this->renderer = _renderer;
}

void GameObject::update(float _dt) {
	//nuthin
}

void GameObject::updateMovement(float _dt) {
	pos.x += (vel.x*_dt);
	pos.y += (vel.y*_dt);

}

void GameObject::draw(bool) {
	//nada
}

bool GameObject::checkIfHover(Vector _mousePos) {
	return 0;
}