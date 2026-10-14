#pragma once
#include "SDL2_Common.h"

class Texture {

private:
	SDL_Rect source;
	float offset;
	SDL_Texture* texture;

public:
	Texture();
	~Texture();
	
	SDL_Rect getSrcRect();
	SDL_Texture* getTexture();
	float getOffset();
	
	void setSrcRect(SDL_Rect s);
	void setTexture(SDL_Texture* t);
	void setOffset(float o);
};