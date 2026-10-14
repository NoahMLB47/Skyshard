#include "TextureManager.hpp"
#include "Renderer.hpp"
#include "Game.hpp"

std::shared_ptr<TextureManager> TextureManager::textureManager = nullptr;

TextureManager::TextureManager()
{
    textures.clear();
    texture = nullptr;
}

TextureManager::~TextureManager()
{
    texture = nullptr;

    for (auto& pair : textures) 
    {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}

std::shared_ptr<TextureManager> TextureManager::instance()
{
    if (!textureManager)
    {
        textureManager.reset(new TextureManager());
        textureManager->init();
    }
    return textureManager;
}

void TextureManager::init()
{
    cacheTextures();
}

SDL_Texture* TextureManager::findTexture(std::string name)
{
    // finding an entry in a map: https://www.geeksforgeeks.org/cpp/map-find-function-in-c-stl/
    auto itt = textures.find(name);
    if (itt != textures.end())
    {
        return itt->second;
    }
    return nullptr;
}

void TextureManager::cacheTexture(std::string name, std::string path)
{
    renderer = Game::instance()->getRenderer();
    SDL_Surface* temp = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer->getRenderer(), temp);

    SDL_FreeSurface(temp);
    temp = nullptr;

    // inserting into map: https://www.geeksforgeeks.org/cpp/map-insert-in-c-stl/
    textures.insert({ name, texture });
}

void TextureManager::cacheTextures()
{
    cacheTexture("player", "assets/images/playerShip.png");
    cacheTexture("background", "assets/images/background.png");
    cacheTexture("smallShip", "assets/images/enemy.png");
    cacheTexture("greenBullet", "assets/images/laser.png");
    
    // https://rehandev.itch.io/280-mega-pixel-space-ship-pack-2d
    cacheTexture("boss", "assets/images/boss.png");
}
