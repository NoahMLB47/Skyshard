#ifndef GAME_OBJECT_FACTORY_HPP
#define GAME_OBJECT_FACTORY_HPP

#include <memory>
#include <string>
#include "SDL2_Common.h"

class Player;
class NPC;
class Background;
class Renderer;
class Bullet;

class GameObjectFactory {

private:
	GameObjectFactory();
	std::shared_ptr<Player> player;
	std::shared_ptr<Background> background;
	std::shared_ptr<NPC> npc;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Bullet> bullet;
	std::string name;

public:
	~GameObjectFactory();

	std::shared_ptr<Player> createPlayer();
	std::shared_ptr<NPC> createNPC();
	std::shared_ptr<Background> createBackground();
	std::shared_ptr<Bullet> createBullet();

	static std::shared_ptr<GameObjectFactory> instance()
	{
		static std::shared_ptr<GameObjectFactory> gameObjectFactory(new GameObjectFactory());
		gameObjectFactory->init();
		return gameObjectFactory;
	}

	void init();
};

#endif