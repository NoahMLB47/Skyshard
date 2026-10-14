#include "NPC.hpp"
#include "PhysicsComponent.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"

NPC::NPC() : GameObject()
{
    npcBulletManager = nullptr;
    timer = nullptr;
    player = nullptr;
}

NPC::~NPC()
{
    npcBulletManager.reset();
    npcBulletManager = nullptr;

    timer.reset();
    timer = nullptr;

    player.reset();
    player = nullptr;
}

void NPC::setSpeed(float speed)
{
    this->speed = speed;
}

float NPC::getSpeed()
{
    return speed;
}

void NPC::setOnDeathCallback(std::function<void()> callback)
{
    onDeathCallback = callback;
}

void NPC::handleCollision(std::shared_ptr<Collider> other)
{
    //speed = 0.0f;
    //std::cout << "NPC says: Ouch!" << std::endl;

    if (other->getGameObject()->getName() == "playerBullet")
    {
        std::shared_ptr<Bullet> bullet = std::static_pointer_cast<Bullet>(other->getGameObject());
        takeDamage(bullet->getDamage());
    }
}
