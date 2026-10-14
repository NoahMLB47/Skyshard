#include "Game.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Timer.hpp"
#include "InputManager.hpp"
#include "RenderEngine.hpp"
#include "Background.hpp"
#include "SDL2_Common.h"
#include "Sprite.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "Vector3f.hpp"
#include "Player.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsEngine.hpp"
#include "GameObjectFactory.hpp"
#include "CollisionEngine.hpp"
#include "NPC.hpp"
#include <iostream>


Game::Game()
{
    quit = false;
    gameWindow = nullptr;
    gameRenderer = nullptr;
    gameTimer = nullptr;
    gameRenderEngine = nullptr;
    gamePhysicsEngine = nullptr;
}

Game::~Game()
{
    gameWindow.reset();
    gameWindow = nullptr;

    gameRenderer.reset();
    gameRenderer = nullptr;

    gameRenderEngine.reset();
    gameRenderEngine = nullptr;
    
    gamePhysicsEngine.reset();
    gamePhysicsEngine = nullptr;
    
    std::vector<std::shared_ptr<GameObject>>::iterator itt;
    for (itt = gameObjects.begin(); itt != gameObjects.end(); itt++)
        (*itt).reset(); // call reset on shared pointer

    gameObjects.clear();

    SDL_Quit();
}

void Game::init()
{
    // SDL allows us to choose which SDL components are  
    // going to be initialised. 
    // Lets go for everything for now!
    SDL_Init(SDL_INIT_EVERYTHING);

    gameWindow = std::shared_ptr<Window>(new Window());
    gameWindow->createSDLWindow();

    gameRenderer = std::shared_ptr<Renderer>(new Renderer());
    gameRenderer->setup(gameWindow->getWindow());
    
    gameObjects.resize(MAX_GAME_OBJECTS);

    gameRenderEngine = std::shared_ptr<RenderEngine>(new RenderEngine());
    gameRenderEngine->init(MAX_GAME_OBJECTS, gameRenderer);

    gameTimer = Timer::instance();
    gameTimer->init();

	inputManager = InputManager::instance();
    inputManager->init();

    gamePhysicsEngine = std::shared_ptr<PhysicsEngine>(new PhysicsEngine());
    gamePhysicsEngine->init(MAX_GAME_OBJECTS);

    gameCollisionEngine = std::shared_ptr<CollisionEngine>(new CollisionEngine());
    gameCollisionEngine->init(MAX_GAME_OBJECTS);

    gameObjectFactory = GameObjectFactory::instance();

    std::shared_ptr<Background> background = gameObjectFactory->createBackground();
    registerGameObjects(background);

    std::shared_ptr<Player> player = gameObjectFactory->createPlayer();
    registerGameObjects(player);

    std::shared_ptr<NPC> npc = gameObjectFactory->createNPC();
    registerGameObjects(npc);
}


void Game::runGameLoop()
{
    gameTimer->update();
    inputManager->update();
    while(!quit)
    {
        gameTimer->update();

        runGameLoopOnce();
    }
}

void Game::cacheTextures()
{
}

void Game::setupGameState()
{

}

void Game::runGameLoopOnce()
{
    float deltaTime = gameTimer->getDeltaTime();
    inputManager->update();
    quit = inputManager->isWindowClosedEvent();

    update(deltaTime);

    draw();
    
    SDL_Delay(0);
}

void Game::update(float deltaTime)
{
    gamePhysicsEngine->update(deltaTime);

    gameCollisionEngine->check();
    
    // update game objects?
    std::shared_ptr<GameObject> object;

    std::vector<std::shared_ptr<GameObject>>::iterator itt;
    for (itt = gameObjects.begin(); itt != gameObjects.end(); itt++)
    {
        object = *itt;
        if(object != nullptr)
           (*itt)->update(); // call reset on shared pointer
    }
}

void Game::draw()
{
    // clear screen
    gameRenderer->clear();

    // draw scene
    gameRenderEngine->render();

    // present current frame to screen
    gameRenderer->present();
}

std::shared_ptr<Renderer> Game::getRenderer()
{
    return gameRenderer;
}

void Game::registerGameObjects(std::shared_ptr<GameObject> newGO)
{
    gameObjects.push_back(newGO);

    std::shared_ptr<Sprite> sprite = newGO->getSprite();

    if (sprite != nullptr)
        gameRenderEngine->addSprite(sprite);

    std::shared_ptr<PhysicsComponent> physicsComponent = newGO->getPhysicsComponent();

    if (physicsComponent != nullptr)
        gamePhysicsEngine->addPhysicsComponent(physicsComponent);

    std::shared_ptr<Collider> col = newGO->getCollider();

    if (col != nullptr)
        gameCollisionEngine->addCollider(col);

}

// returns first thing with that name
std::shared_ptr<GameObject> Game::findGameObjectByName(std::string name)
{
    std::shared_ptr<GameObject> object;
    std::shared_ptr<GameObject> found = nullptr;

    std::vector<std::shared_ptr<GameObject>>::iterator itt;
    for (itt = gameObjects.begin(); itt != gameObjects.end(); itt++)
    {
        object = *itt;
        
        if (object == nullptr)
            continue;

        if (object->getName() == name)
        {
            found = object;
            break;
        }
    }

    return found;
}
