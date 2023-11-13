#include "Game.h"
#include "ExternDecl.h"

int main(int num_args, char* argv[]) {
	const int SCREEN_WIDTH = 950;
	const int SCREEN_HEIGHT = 550;

	Game* game = nullptr;

	const int FPS = 60;
	const int delta = 1000 / FPS;
	int startLoop, frameTime;

	game = new Game();

	if (!game->init("DINO DASH", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN))
		return -1;

	while (game->running()) {
		startLoop = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - startLoop;

		if (frameTime < delta) {
			SDL_Delay(delta - frameTime);
		}
	}

	game->clean();
	delete game;
	game = nullptr;

	return 0;
}