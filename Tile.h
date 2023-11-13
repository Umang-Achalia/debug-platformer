#pragma once

#include <SDL.h>

class Tile {
public:
	Tile();
	~Tile();

	bool create(int x, int y, const char* texturePath, const float scale, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer, const SDL_Rect* camera);

public:
	SDL_Rect* getTile() { return &tile; }

private:
	SDL_Rect src, tile;
	SDL_Texture* texture;
};