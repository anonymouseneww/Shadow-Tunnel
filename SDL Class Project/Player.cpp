#include "Player.h"

Player::Player() {}
Player::~Player() {}

void Player::setAnimation(Animation *animation) {
	this->animation = animation;
}

void Player::update(float dt) {
	// Check horizontal direction
	if (vel.x > 0) {
		faceRight = true;
	} else if (vel.x < 0) {
		faceRight = false;
	}

	// Character Controller
	updateMovement(dt);

	// Update Animation
	animation->update(dt);
}

void Player::draw() {
	if (animation != NULL) {
		if (faceRight)
			animation->draw(pos.x, pos.y);
		else
			animation->draw(pos.x, pos.y, true);



	}
}

