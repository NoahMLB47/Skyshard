#include "TextBox.hpp"
#include "SDL2_Common.h"
#include <string>
#include "Vector3f.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Window.hpp"

TextBox::TextBox() : GameObject()
{

}

TextBox::~TextBox()
{
	
}

void TextBox::update()
{

}

void TextBox::handleCollision(std::shared_ptr<Collider> other)
{

}

void TextBox::updateMessage(std::string newMessage, SDL_Renderer* renderer)
{
    // Sprite
    std::shared_ptr<Sprite> textBoxSprite = this->getSprite();

    // Texture
    std::shared_ptr<Texture> textBoxTexture = textBoxSprite->getTexture();
    
    float textScale = Window::WINDOW_WIDTH * 0.02083333333f;

    TTF_Font* sans = TTF_OpenFont("assets/fonts/SansSerifCollection.ttf", textScale);

    SDL_Color white = { 255, 255, 255 };

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, newMessage.c_str(), white);

    // now you can convert it into a texture
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    textBoxTexture->setTexture(messageTexture);

    SDL_Rect message_rect;
    message_rect.x = 0;
    message_rect.y = 0;
    message_rect.w = 100;
    message_rect.h = 100;

    SDL_QueryTexture(textBoxTexture->getTexture(), NULL, NULL, &message_rect.w, &message_rect.h);
    textBoxTexture->setSourceRectangle(message_rect);

    textBoxSprite->setTexture(textBoxTexture);
}
