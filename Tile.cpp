#include "Tile.h"
#include <SDL_image.h>
#include "ExternDecl.h"

Tile::Tile() {

}

Tile::~Tile() {

}

bool Tile::create(int x, int y, const char* texturePath, const float scale, SDL_Renderer* renderer) {
	texture = IMG_LoadTexture(renderer, texturePath);

	if (!texture)
	{
		printf("Error: failed to create texture '%s'. %s\n", texturePath, SDL_GetError());

		return false;
	}

	int width = 0;
	int height = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	src.x = 0;
	src.y = 0;
	src.w = width;
	src.h = height;

	tile.x = x;
	tile.y = y;
	tile.w = (int)((float)src.w * scale);
	tile.h = (int)((float)src.h * scale);

	return true;
}

void Tile::draw(SDL_Renderer* renderer, const SDL_Rect* camera) {
	const SDL_Rect tileRect = { tile.x - camera->x, tile.y - camera->y, tile.w, tile.h };
	SDL_RenderCopy(renderer, texture, &src, &tileRect);

	// Debug drawing

//	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
//	SDL_RenderDrawRect(renderer, &tileRect);
}