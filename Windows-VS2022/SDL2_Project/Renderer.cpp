#include "Renderer.hpp"
#include "SDL2_Common.h"

Renderer::Renderer()
{
	renderer = nullptr;
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}

void Renderer::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}

SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}

SDL_Renderer* Renderer::setup(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, 0, 0);

	return renderer;
}

void Renderer::clear()
{
	// 1. Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	// Colour provided as red, green, blue and alpha (transparency) values (ie. RGBA)

	SDL_RenderClear(renderer);
}

void Renderer::present()
{
	SDL_RenderPresent(renderer);
}
