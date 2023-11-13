#include "Entity.h"
#include <SDL_image.h>

#include "ExternDecl.h"

bool Entity::create(SDL_Renderer* renderer, const char* texturePath, const SDL_FPoint& startPosition){
	texture = IMG_LoadTexture(renderer, texturePath);

	if (!texture)
	{
		printf("Error: failed to create texture '%s'. %s\n", texturePath, SDL_GetError());

		return false;
	}

	position = startPosition;

	return true;
}

void Entity::draw(SDL_Renderer* renderer, const SDL_Rect* camera) {
	const SDL_Rect entityRectWorld = {dest.x - camera->x, dest.y - camera->y, dest.w, dest.h};

	SDL_RenderCopy(renderer, texture, &src, &entityRectWorld);
}