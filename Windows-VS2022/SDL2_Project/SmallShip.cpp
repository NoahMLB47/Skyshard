#include "SmallShip.hpp"
#include "NPC.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Transform.hpp"
#include "Game.hpp"
#include "NPCBulletManager.hpp"
#include "Timer.hpp"
#include "UI.hpp"

#include <iostream> 

SmallShip::SmallShip() : NPC()
{
    speed = 300.0f;
    hp = MAX_HP;
    name = "smallShip";
    fireCooldown = 0.0f;
    canFire = true;
    onDeathCallback = nullptr;

    timer = Timer::instance();
    player = Game::instance()->findGameObjectByName("player");
}

SmallShip::~SmallShip()
{}

void SmallShip::update()
{
    if (hp > 0)
    {
        ai();
    }

    // Cooldown
    if (fireCooldown > 0.0f)
    {
        float deltaTime = timer->getDeltaTime();
        fireCooldown -= deltaTime;
    }

    else
    {
        canFire = true;
    }
}

void SmallShip::init()
{
    npcBulletManager = NPCBulletManager::instance();
}

void SmallShip::ai()
{
    if (player != nullptr)
    {
        std::shared_ptr<Vector3f> playerPos = player->getTransform()->getPosition();

        std::shared_ptr<Vector3f> myPosition = transform->getPosition();
        Vector3f toPlayer(playerPos);

        toPlayer.sub(myPosition);
        toPlayer.normalise();
        toPlayer.scale(speed);

        std::shared_ptr<Vector3f> centre = transform->getPosition();

        physicsComponent->getVelocity()->assign(toPlayer);

        // rotation

        float angleRads = atan2f(toPlayer.getY(), toPlayer.getX());
        float angleDegrees = angleRads * (180.0f / M_PI); // convert to degrees
        this->getTransform()->setAngle(angleDegrees + 90.0f);

        // firing

        if (canFire && this->isEnabled())
        {
            canFire = false;
            fireCooldown = FIRE_RATE;
            Vector3f bulletDirection(0.0f, -1.0f, 0.0f);
            float rotation = angleRads + (90.0f * (M_PI / 180.0f));
            bulletDirection.rotate2D(rotation);

            //std::cout << "direction:" << bulletDirection->getX() << "," << bulletDirection->getY() << std::endl;
            //std::cout << "angle:" << angleRads << std::endl;

            Vector3f position(transform->getPosition());

            Vector3f offset(bulletDirection);
            offset.scale(64);
            position.add(offset);

            npcBulletManager->spawnBullet(position, bulletDirection, rotation * (180.0f / M_PI));
        }
    }
}

void SmallShip::takeDamage(int damageDone)
{
    hp -= damageDone;

    //std::cout << hp << std::endl;

    if (hp <= 0)
    {
        hp = MAX_HP;
        UI::instance()->updateScore(20);
        this->disable();

        if (onDeathCallback != nullptr)
        {
            //std::cout << "death" << std::endl;
            onDeathCallback();
        }
    }
}
