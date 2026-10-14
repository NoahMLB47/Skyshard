#pragma once

#include "SDL2_Common.h"

class Window {

public:
	Window();
	~Window();

	void setWindow(SDL_Window* w);
	SDL_Window* getWindow();

	SDL_Window* createSDLWindow();

private:
	SDL_Window* window;

public:
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 600;
};