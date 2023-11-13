#include "Game.h"

#include "Player.h"
#include "Tile.h"
#include "TileMap.h"

#include <iostream>
#include <vector>

std::vector<Tile*> group_of_tiles;

Game::Game() {

}

Game::~Game() {

}

bool Game::init(const char* title ,int x, int y, int w, int h, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, x, y, w, h, flags);

		if (!window)
		{
			printf("Error: failed to create window. %s\n", SDL_GetError());

			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED | SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC);

		if (!renderer)
		{
			printf("Error: failed to create renderer. %s\n", SDL_GetError());

			return false;
		}
	}

	player = new Player;
	if (!player->create(renderer, "assets/hobbit.png", {90.0, 90.0f}))
		return false;

	level1 = new LevelMaker;
	if (!level1->create(renderer, tile_map, "assets/floating.png", "assets/extensions/mudUp1.png", "assets/top_grass/top1.png", "assets/top_grass/top2.png", "assets/top_grass/top3.png", "assets/mid_grass/middle1.png", "assets/mid_grass/middle2.png", "assets/mid_grass/middle3.png", "assets/bot_grass/bottom1.png", "assets/bot_grass/bottom2.png", "assets/bot_grass/bottom3.png", "assets/extensions/grassUp1.png", "assets/extensions/mudDown1.png", "assets/extensions/grassUp2.png"))
		return false;

	camera = new Camera(w, h);
	camera->setBounds({0, 0}, level1->getSize());

	return true;
}

void Game::clean() {
	delete camera;
	camera = nullptr;

	level1->destroy();
	delete level1;
	level1 = nullptr;

	delete player;
	player = nullptr;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::handleEvent() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {

		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
}

void Game::update() {
	player->update();

	camera->setPos(player->getPos());
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// ------------------------------------------

	SDL_Rect* cameraRect = camera->getRect();

	player->draw(renderer, cameraRect);
    
	for (int count = 0; count < group_of_tiles.size(); count++) {
		group_of_tiles[count]->draw(renderer, cameraRect);
	}

//	cam->draw();

	// ------------------------------------------

	SDL_RenderPresent(renderer);
}