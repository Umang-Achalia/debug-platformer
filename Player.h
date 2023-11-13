#pragma once

#include "Entity.h"

class Player : public Entity {
public:

	 Player(void);
	~Player(void);

	virtual bool create(SDL_Renderer* renderer, const char* texturePath, const SDL_FPoint& startPosition) override;
	virtual void update() override;
	virtual void draw(SDL_Renderer* renderer, const SDL_Rect* camera) override;

private:

	void handleInput();
	void resolveXCollision(SDL_Rect* tileRect, const float moveAmount);
	void resolveYCollision(SDL_Rect* tileRect, const float moveAmoun);
	void syncCollisionRects();

private:

	SDL_Rect horizontalDetector = {0, 0, 0, 0};
	SDL_Rect verticalDetector = {0, 0, 0, 0};

	// HORIZONTAL
	float accelerationX = 0.0f;
	float accelerationSpeedX = 0.5f;
	float deaccelerationSpeedX = 0.5f;
	float accelerationMaxX = 5.0f;

	// VERTICAL
	float accelerationY = 0.0f;
	float gravity = 2.0f;
	float gravityMax = 7.0f;
	float jumpStrength = 22.0f;

	bool onGround = false;
	bool spaceHeld = false;

};