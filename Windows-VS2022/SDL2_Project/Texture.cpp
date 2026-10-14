#include "Texture.hpp"
#include "Sprite.hpp"

Texture::Texture()
{
    source.x = 0;
    source.y = 0;
    source.w = 0;
    source.h = 0;

    offset = 0.0f;
    texture = nullptr;
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

SDL_Rect Texture::getSrcRect()
{
    return source;
}

SDL_Texture* Texture::getTexture()
{
    return texture;
}

float Texture::getOffset()
{
    return offset;
}


void Texture::setSrcRect(SDL_Rect s)
{
    source = s;
}

void Texture::setTexture(SDL_Texture* t)
{
    texture = t;
}

void Texture::setOffset(float o)
{
    offset = o;
}
