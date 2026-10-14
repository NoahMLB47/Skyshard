#pragma once

#include "SDL2_Common.h"

class Renderer {

public:
	Renderer();
	~Renderer();

	void setRenderer(SDL_Renderer* r);
	SDL_Renderer* getRenderer();

	SDL_Renderer* setup(SDL_Window* window);

	void clear();
	void present();

private:
	SDL_Renderer* renderer;
};