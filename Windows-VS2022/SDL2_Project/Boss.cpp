#include "Boss.hpp"
#include "NPC.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Transform.hpp"
#include "Game.hpp"
#include "NPCBulletManager.hpp"
#include "Timer.hpp"
#include "Window.hpp"
#include "UI.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Collider.hpp"

#include <iostream>
#include <cmath>

Boss::Boss() : NPC()
{
    speed = 100.0f;
    hp = MAX_HP;
    name = "boss";
    fireCooldown = 0.0f;
    canFire = true;
    onDeathCallback = nullptr;

    timer = Timer::instance();
    player = Game::instance()->findGameObjectByName("player");
}

Boss::~Boss()
{
    onDeathCallback = nullptr;
}

void Boss::update()
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

void Boss::init()
{
    npcBulletManager = NPCBulletManager::instance();
    position = this->getTransform()->getPosition();

    physicsComponent->getVelocity()->scale(speed);
}

void Boss::ai()
{
    if (position->getX() <= Window::WINDOW_WIDTH * 0.6)
    {
        speed = 0.0f;
        physicsComponent->getVelocity()->scale(speed);
    }

    if (player != nullptr)
    {
        std::shared_ptr<Vector3f> playerPos = player->getTransform()->getPosition();

        std::shared_ptr<Vector3f> myPosition = transform->getPosition();
        Vector3f toPlayer(playerPos);

        toPlayer.sub(myPosition);
        toPlayer.normalise();

        std::shared_ptr<Vector3f> centre = transform->getPosition();

        // rotation

        float angleRads = atan2f(toPlayer.getY(), toPlayer.getX());
        float angleDegrees = angleRads * (180.0f / M_PI); // convert to degrees
        this->getTransform()->setAngle(angleDegrees + 180.0f);

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

            position.setX(position.getX() + (cosf(angleRads) * collider->getRadius()));
            position.setY(position.getY() + (sinf(angleRads) * collider->getRadius()));


            //Vector3f offset(bulletDirection);
           // offset.scale(1);
           // position.add(offset);
            position.setY(position.getY() + 50.0f);

            npcBulletManager->spawnBullet(position, bulletDirection, rotation * (180.0f / M_PI));

            position.setY(position.getY() -100.0f);

            npcBulletManager->spawnBullet(position, bulletDirection, rotation * (180.0f / M_PI));

        }
    }
}

void Boss::takeDamage(int damageDone)
{
    hp -= damageDone;

    //std::cout << hp << std::endl;

    if (hp <= 0)
    {
        hp = MAX_HP;
        UI::instance()->updateScore(500);
        UI::instance()->enableLevelComplete();
        this->disable();

        if (onDeathCallback != nullptr)
        {
            //std::cout << "death" << std::endl;
            onDeathCallback();
        }
    }
}
