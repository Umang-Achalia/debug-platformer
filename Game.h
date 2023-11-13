#pragma once

#include "Camera.h"
#include "Entity.h"
#include "LevelMaker.h"

#include <SDL.h>

class Game {
public:
	Game();
	~Game();

	bool init(const char*, int, int, int, int, int);
	void clean();
	void handleEvent();
	void update();
	void render();

public:
	bool running() { return isRunning; }

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Entity* player = nullptr;

	LevelMaker* level1 = nullptr;

	Camera* camera = nullptr;

	bool isRunning = true;
};