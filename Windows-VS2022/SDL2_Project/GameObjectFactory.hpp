#ifndef GAMEOBJECTFACTORY_HPP
#define GAMEOBJECTFACTORY_HPP

#include "SDL2_Common.h"

#include <memory>
#include <string>

class Background;
class Player;
class Renderer; 
class SmallShip;
class Bullet;
class Vector3f;
class TextureManager;
class Boss;
class TextBox;

class GameObjectFactory
{
private:
	// Singleton - private constructor!
	GameObjectFactory();
	void init();

	static std::shared_ptr<GameObjectFactory> gof;

    std::shared_ptr<Renderer> renderer;
	std::shared_ptr<TextureManager> textureManager;

public:
	static std::shared_ptr<GameObjectFactory> instance();
	
    ~GameObjectFactory();

    std::shared_ptr<Background> createBackground(std::shared_ptr<Vector3f> position);
    std::shared_ptr<Player> createPlayer();
    std::shared_ptr<SmallShip> createSmallShip(std::shared_ptr<Vector3f> position);
	std::shared_ptr<Bullet> createBullet(std::string name);
	std::shared_ptr<Boss> createBoss();
	std::shared_ptr<TextBox> createTextBox(std::string message, std::shared_ptr<Vector3f> position, SDL_Renderer* renderer);

	const int MAX_BULLETS = 32;
};

#endif