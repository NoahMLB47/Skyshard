#ifndef NPC_HPP
#define NPC_HPP


#include "GameObject.hpp"
#include <memory>
#include <functional>

class NPCBulletManager;
class Timer;
class Player;

class NPC : public GameObject {

public:
    NPC();
    virtual ~NPC();

    void setSpeed(float speed);
    float getSpeed();

    virtual void ai() = 0;
    virtual void takeDamage(int damage) = 0;
    void setOnDeathCallback(std::function<void()> callback);
    void handleCollision(std::shared_ptr<Collider> other);

protected:
    float speed;
    float fireCooldown;
    bool canFire;
    int hp;

    std::shared_ptr<NPCBulletManager> npcBulletManager;
    std::shared_ptr<Timer> timer;
    std::shared_ptr<GameObject> player;

    std::function<void()> onDeathCallback;
};

#endif