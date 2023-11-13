#pragma once

#include <SDL.h>

class LevelMaker {

public:

	bool create(SDL_Renderer* renderer, const char*[], const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*);
	void destroy();

public:

	SDL_Point getSize() const {return size;}

private:

	SDL_Point size;

};