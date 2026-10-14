#include "NPCManager.hpp"

#include "SmallShip.hpp"
#include "Boss.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"
#include "GameObjectFactory.hpp"
#include "Window.hpp"
#include "Game.hpp"

#include <iostream>
#include <random>

NPCManager::NPCManager()
{
    maxObjects = 20;
    killCount = 0;

    gameObjectFactory = nullptr;
}

NPCManager::~NPCManager()
{
    std::vector<std::shared_ptr<SmallShip>>::iterator itt;
    for (itt = smallShips.begin(); itt != smallShips.end(); ++itt)
    {
        (*itt).reset(); // call reset on the shared pointer!
    }

    smallShips.clear();

    gameObjectFactory.reset();
    gameObjectFactory = nullptr;

}

void NPCManager::init(int maxObjects)
{
    gameObjectFactory = GameObjectFactory::instance();

    smallShips.resize(maxObjects);

    // create npcs - using factory
    std::vector<std::shared_ptr<SmallShip>>::iterator itt;
    for (itt = smallShips.begin(); itt != smallShips.end(); ++itt)
    {
        std::shared_ptr<Vector3f> nextPos = std::shared_ptr<Vector3f>(new Vector3f(0.0f, 0.0f, 0.0f));

        float x = randomX();
        float y = randomY(x);

        nextPos->setX(x);
        nextPos->setY(y);
        
        (*itt) = gameObjectFactory->createSmallShip(nextPos);
        (*itt)->init();
        (*itt)->setOnDeathCallback([this]() {this->onNPCDeath(); });
        
        int index = std::distance(smallShips.begin(), itt);

        if (index < Game::MAX_NPCS/2)
        {
            (*itt)->enable();
        }
    }

    std::shared_ptr<Boss> boss = gameObjectFactory->createBoss();
    boss->init();
}

void NPCManager::spawnNPC()
{
    std::shared_ptr<SmallShip> npc = this->nextFreeSmallShip();

    if (npc != nullptr)
    {
        float x = randomX();
        float y = randomY(x);

        npc->getTransform()->getPosition()->setX(x);
        npc->getTransform()->getPosition()->setY(y);
        
        npc->enable();
       // std::cout << "NPC manager spawning" << std::endl;
    }
    else
    {
        //std::cout << "NPC manager has no NPCs" << std::endl;
    }

    // if no NPCs just ignore?
}

void NPCManager::onNPCDeath()
{
    killCount += 1;

    if (killCount >= MAX_KILLS)
    {
        disableAll();
        std::shared_ptr<GameObject> boss = Game::instance()->findGameObjectByName("boss");
        boss->enable();
        std::cout << "boss enabled" << std::endl;
    }
    
    else
    {
        spawnNPC();
    }
}

void NPCManager::disableAll()
{
    std::vector<std::shared_ptr<SmallShip>>::iterator itt;
    for (itt = smallShips.begin(); itt != smallShips.end(); ++itt)
    {
        if (*itt != nullptr)
        {
            (*itt)->disable();
        }
    }
}

std::shared_ptr<SmallShip> NPCManager::nextFreeSmallShip()
{
    std::vector<std::shared_ptr<SmallShip>>::iterator itt;
    for (itt = smallShips.begin(); itt != smallShips.end(); ++itt)
    {
        std::shared_ptr<NPC> temp = *itt;
        if ((*itt)->isEnabled() == false)
            return (*itt);
    }

    return nullptr;
}

std::mt19937& NPCManager::getRandomEngine()
{
    std::random_device rd;
    std::mt19937 engine(rd());
    return engine;
}

float NPCManager::randomX()
{
    std::uniform_real_distribution<float> distribution(Window::WINDOW_WIDTH * 0.75f, Window::WINDOW_WIDTH * 1.25f);

    return distribution(getRandomEngine());
}

float NPCManager::randomY(float x)
{
    if (x < Window::WINDOW_WIDTH)
    {
        std::uniform_int_distribution<int> topOrBottom(0, 1);
        int choice = topOrBottom(getRandomEngine());
        if (choice == 0)
        {
            std::uniform_real_distribution<float> distribution(-(Window::WINDOW_HEIGHT * 0.25f), 0.0f);

            return distribution(getRandomEngine());
        }

        else if (choice == 1)
        {
            std::uniform_real_distribution<float> distribution(Window::WINDOW_HEIGHT, Window::WINDOW_HEIGHT * 1.25f);

            return distribution(getRandomEngine());
        }
    }

    else if (x >= Window::WINDOW_WIDTH)
    {
        std::uniform_real_distribution<float> distribution(-(Window::WINDOW_HEIGHT * 0.25f), (Window::WINDOW_HEIGHT * 1.25f));

        return distribution(getRandomEngine());
    }
}
