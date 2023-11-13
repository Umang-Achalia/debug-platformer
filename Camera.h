#pragma once

#include <SDL.h>

class Camera {
public:
	Camera();
	Camera(const int width, const int height);
	~Camera();

	void draw(SDL_Renderer* renderer);

	void setBounds(const SDL_Point& min, const SDL_Point& max);

public:
	SDL_Point getPos() const {return {rect.x, rect.y};}
	void setPos(const SDL_Point& position);

	SDL_Point getSize() const {return {rect.w, rect.h};}

	SDL_Rect* getRect() { return &rect; }

private:
	SDL_Rect rect = {0, 0, 0, 0};

	SDL_Point minPosition;
	SDL_Point maxPosition;

};