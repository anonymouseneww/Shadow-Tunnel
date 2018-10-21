#include "Player.h"

Player::Player(int animationNumber, int x, int y) {
	switch (animationNumber) {
	case 0:
		animatedSurface = IMG_Load("Assets/Character/GoldGuy.png");
		break;

	case 1:
		animatedSurface = IMG_Load("Assets/Character/OldKing.png");
		break;

	case 2:
		animatedSurface = IMG_Load("Assets/Character/GreenZeldaGuy.png");
		break;
	}

	// Make the background transparent
	//SDL_SetColorKey(animatedSurface, 1, SDL_MapRGB(animatedSurface->format, 128, 128, 255));

	playerTexture = SDL_CreateTextureFromSurface(Globals::renderer, animatedSurface);
	SDL_FreeSurface(animatedSurface);

	animation = new Animation(playerTexture, Globals::renderer, 23, 32, 32, 0.8);

	this->pos.x = x;
	this->pos.y = y;
}


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

void Player::draw(bool) {
	if (animation != NULL) {
		if (faceRight)
			animation->draw(pos.x, pos.y);
		else
			animation->draw(pos.x, pos.y, true);
	}
}

