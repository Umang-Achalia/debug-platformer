#pragma once

#include <SDL.h>

class Entity {
public:
	Entity() {}
	virtual ~Entity() { SDL_DestroyTexture(texture); }

	virtual bool create(SDL_Renderer* renderer, const char* texturePath, const SDL_FPoint& startPosition);
	virtual void update() {}
	virtual void draw(SDL_Renderer* renderer, const SDL_Rect* camera);

public:
	SDL_Point getPos() const {return {dest.x, dest.y};}
	SDL_Point getSize() const {return {dest.w, dest.h};}

	SDL_Rect* getRect() { return &dest; }

protected:
	SDL_Texture* texture = nullptr;

	SDL_FPoint position = {0.0f, 0.0f};

	SDL_Rect src = {0, 0, 0, 0};
	SDL_Rect dest = {0, 0, 0, 0};

};