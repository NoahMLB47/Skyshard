#include "Player.hpp"
#include "InputManager.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Collider.hpp"
#include "BulletManager.hpp"
#include "Transform.hpp"

#include "Timer.hpp"
#include "Bullet.hpp"
#include "UI.hpp"

#include "Sprite.hpp"
#include "Texture.hpp"

#include "Window.hpp"

#include <iostream>  

const float Player::FIRE_RATE = 0.1f;

Player::Player() : GameObject()
{
    speed = 500.0f;
    name = "player";
    hp = MAX_HP;
    bulletManager = nullptr;
    fireCooldown = 0.0f;
    canFire = true;

    timer = nullptr;

}

Player::~Player()
{
    bulletManager.reset();
    bulletManager = nullptr;

    timer.reset();
    timer = nullptr;
}

void Player::update()
{

    // Movement. 

    float horizontal = InputManager::instance()->getHorizontalInput();
    float vertical = InputManager::instance()->getVerticalInput();

    std::shared_ptr<Vector3f> velocity = physicsComponent->getVelocity();

    velocity->setX(horizontal);
    
    velocity->setY(vertical);

    // normalise or diagonals are faster. 
   // velocity->normalise();

    // scale by speed.
    velocity->scale(speed);

    // No need to do a set - accessing the velocity directly :-P

    if (transform->getPosition()->getY() > Window::WINDOW_HEIGHT)
    {
        transform->getPosition()->setY(0.0f);
    }

    else if (transform->getPosition()->getY() < 0.0f)
    {
        transform->getPosition()->setY(Window::WINDOW_HEIGHT);
    }

    if (transform->getPosition()->getX() < 0.0f)
    {
        transform->getPosition()->setX(0.0f);
    }

    else if (transform->getPosition()->getX() > Window::WINDOW_WIDTH)
    {
        transform->getPosition()->setX(Window::WINDOW_WIDTH);
    }

    // Rotation

    std::shared_ptr<Vector3f> mousePos = InputManager::instance()->getMousePosition();
    std::shared_ptr<Vector3f> centre = transform->getPosition();

    float angleRads = atan2f(mousePos->getY() - centre->getY(), mousePos->getX() - centre->getX());
    float angleDegrees = angleRads * (180.0f/M_PI); // convert to degrees
    this->getTransform()->setAngle(angleDegrees);

    // Firing

    if (fireCooldown > 0.0f)
    {
        float deltaTime = timer->getDeltaTime();
        fireCooldown -= deltaTime;
    }

    else
    {
        canFire = true;
    }


    if(InputManager::instance()->getFire() == true && canFire == true && this->isEnabled())
    {
        canFire = false;
        fireCooldown = FIRE_RATE;
        Vector3f bulletDirection(0.0f, -1.0f, 0.0f);
        float rotation = angleRads + (this->getSprite()->getTexture()->getAngleOffset() * (M_PI/180.0f));
        bulletDirection.rotate2D(rotation);

       // std::cout << "direction:" << bulletDirection->getX() << "," << bulletDirection->getY() << std::endl;
      //  std::cout << "angle:" << angleRads << std::endl;

        Vector3f position(transform->getPosition());

        Vector3f offset(bulletDirection);
        offset.scale(64);
        position.add(offset);

        bulletManager->spawnBullet(position, bulletDirection, rotation * (180.0f/M_PI));

    }
}

void Player::setSpeed(float speed)
{
    this->speed = speed;
}

float Player::getSpeed()
{
    return speed;
}

void Player::handleCollision(std::shared_ptr<Collider> other)
{
    //std::cout << "Player says: Ouch!" << std::endl;

    //if(other->getGameObject()->getName() == "NPC")
    //{
    //    std::shared_ptr<NPC> npc = std::static_pointer_cast<NPC>(other->getGameObject());
    //    takeDamage(npc->getDamage());
    //}
     
    if (other->getGameObject()->getName() == "npcBullet")
    {
        std::shared_ptr<Bullet> bullet = std::static_pointer_cast<Bullet > (other->getGameObject());
        takeDamage(bullet->getDamage());
    }
}

void Player::init(int maxBullets)
{
    timer = Timer::instance();
 
    bulletManager.reset(new BulletManager());
    bulletManager->init(MAX_BULLETS);
}

void Player::takeDamage(int damage)
{
    hp -= damage;

    UI::instance()->updateHealth(std::to_string(hp));

    if (hp <= 0)
    {
        // TODO: game logic
        UI::instance()->enableGameOver();
        this->disable();
    }

   // std::cout << hp << std::endl;
}