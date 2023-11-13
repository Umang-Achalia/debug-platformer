#include "Player.h"

#include "ExternDecl.h"

// std::min, std::max
#include <algorithm>

Player::Player(void) {

}

Player::~Player(void) {

}

bool Player::create(SDL_Renderer* renderer, const char* texturePath, const SDL_FPoint& startPosition) {
	if (!Entity::create(renderer, texturePath, startPosition))
		return false;

	int width = 0;
	int height = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	src.w = width;
	src.h = height;

	dest.w = src.w * 3;
	dest.h = src.h * 3;

	horizontalDetector.w = 45;
	horizontalDetector.h = 10;

	verticalDetector.w = 24;
	verticalDetector.h = 45;

	syncCollisionRects();

	return true;
}

void Player::update() {
	handleInput();

	accelerationY = std::min(accelerationY + gravity, gravityMax);

	position.x += accelerationX;
	position.y += accelerationY;

	syncCollisionRects();

	for(Tile* tile : group_of_tiles)
	{
		SDL_Rect* tileRect = tile->getTile();

		resolveXCollision(tileRect, accelerationX);
		resolveYCollision(tileRect, accelerationY);
	}
}

void Player::draw(SDL_Renderer* renderer, const SDL_Rect* camera) {
	Entity::draw(renderer, camera);

	// Debug drawing

//	const SDL_Rect horizontalRectWorld	= {horizontalDetector.x - camera->x, horizontalDetector.y	- camera->y, horizontalDetector.w,	horizontalDetector.h};
//	const SDL_Rect verticalRectWorld	= {verticalDetector.x	- camera->x, verticalDetector.y		- camera->y, verticalDetector.w,	verticalDetector.h};
//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//	SDL_RenderDrawRect(renderer, &horizontalRectWorld);
//	SDL_RenderDrawRect(renderer, &verticalRectWorld);
}

void Player::handleInput() {
	const Uint8* keyboardState = SDL_GetKeyboardState(0);

	// Accelerate the player to move to the left, until max acceleration speed is reached
	if (keyboardState[SDL_GetScancodeFromKey(SDLK_LEFT)]) {
		accelerationX = std::max(accelerationX - accelerationSpeedX, -accelerationMaxX);
	}

	// Accelerate the player to move to the right, until max acceleration speed is reached
	else if (keyboardState[SDL_GetScancodeFromKey(SDLK_RIGHT)]) {
		accelerationX = std::min(accelerationX + accelerationSpeedX, accelerationMaxX);
	}

	// Neither A or D is pressed, deaccelerate the player until full stop
	else {
		if (accelerationX < 0.0f) {
			accelerationX = std::min(accelerationX + deaccelerationSpeedX, 0.0f);
		}

		else if (accelerationX > 0.0f) {
			accelerationX = std::max(accelerationX - deaccelerationSpeedX, 0.0f);
		}
	}

	if (keyboardState[SDL_GetScancodeFromKey(SDLK_SPACE)]) {

		// This is to make sure that the player can't hold the space key to jump continuously, the space key needs to be released for the player to be able to jump again
		if (onGround && !spaceHeld) {
			accelerationY = -jumpStrength;

			onGround = false;

			spaceHeld = true;
		}
	}

	else {
		spaceHeld = false;
	}
}

void Player::resolveXCollision(SDL_Rect* tileRect, const float moveAmount) {
	SDL_Rect intersection = {0, 0, 0, 0};

	// check for collision between tiles and player's horizontal detector
	if(SDL_IntersectRect(tileRect, &horizontalDetector, &intersection)) {
		// The player is moving to the left
		if(moveAmount < 0.0f)
			position.x += (float)intersection.w;

		// The player is moving to the right
		else if(moveAmount > 0.0f)
			position.x -= (float)intersection.w;

		// Player is standing still
		else
		{
			if(horizontalDetector.x > tileRect->x)
				position.x += (float)intersection.w;

			else
				position.x -= (float)intersection.w;
		}

		accelerationX = 0.0f;
	}

	syncCollisionRects();
}

void Player::resolveYCollision(SDL_Rect* tileRect, const float moveAmount) {
	SDL_Rect intersection = {0, 0, 0, 0};

	if(SDL_IntersectRect(tileRect, &verticalDetector, &intersection))
	{
		// The player is jumping
		if(moveAmount < 0.0f)
			position.y += (float)intersection.h;

		// The player is moving down (due to gravity)
		else if(moveAmount > 0.0f)
		{
			position.y -= (float)intersection.h;

			onGround = true;
		}

		accelerationY = 0.0f;
	}

	syncCollisionRects();
}

void Player::syncCollisionRects() {
	dest.x = (int)position.x;
	dest.y = (int)position.y;

	horizontalDetector.x = dest.x + 5;
	horizontalDetector.y = dest.y + 20;

	verticalDetector.x = dest.x + 24;
	verticalDetector.y = dest.y + 5;
}