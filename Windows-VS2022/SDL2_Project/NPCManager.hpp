#ifndef NPC_MANAGER_HPP
#define NPC_MANAGER_HPP

#include <vector>
#include <memory>
#include <random>

class NPC;
class Vector3f;
class GameObjectFactory;
class SmallShip;

class NPCManager {

public:
    NPCManager();
    ~NPCManager();

    void init(int maxObjects);

    void spawnNPC();
    void onNPCDeath();
    void disableAll();

private:
    int maxObjects;
    int killCount;
    std::vector<std::shared_ptr<SmallShip>> smallShips;

    std::shared_ptr<SmallShip> nextFreeSmallShip();
    std::mt19937& getRandomEngine();
    float randomX();
    float randomY(float x);

    std::shared_ptr<GameObjectFactory> gameObjectFactory;

    const int MAX_KILLS = 20;
};

#endif