#pragma once

#include "Window.hpp"
#include "Renderer.hpp"
#include "Timer.hpp"
#include "InputManager.hpp"
#include "SDL2_Common.h"
#include <memory>
#include <vector>
#include <string>

class RenderEngine;
class PhysicsEngine;
class GameObjectFactory;
class GameObject;
class CollisionEngine;

class Game {

public:
	~Game();

	void init();
	void runGameLoop();
	void cacheTextures();
	void setupGameState();
	std::shared_ptr<Renderer> getRenderer();

	static const int MAX_GAME_OBJECTS = 32;

	static std::shared_ptr<Game> instance()
	{
		static std::shared_ptr<Game> game(new Game());
		return game;
	}

	void registerGameObjects(std::shared_ptr<GameObject> newGO);
	std::shared_ptr<GameObject> findGameObjectByName(std::string name);

private:
	Game();

	std::shared_ptr<Window> gameWindow;
	std::shared_ptr<Renderer> gameRenderer;
	std::shared_ptr<RenderEngine> gameRenderEngine;
	std::shared_ptr<Timer> gameTimer;
	std::shared_ptr<InputManager> inputManager;
	std::shared_ptr<PhysicsEngine> gamePhysicsEngine;
	std::shared_ptr<GameObjectFactory> gameObjectFactory;
	std::shared_ptr<CollisionEngine> gameCollisionEngine;
	bool quit;

	std::vector<std::shared_ptr<GameObject>> gameObjects;
	void runGameLoopOnce();
	void update(float deltaTime);
	void draw();
};
