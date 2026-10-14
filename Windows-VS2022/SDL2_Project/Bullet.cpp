#include "Bullet.hpp"
#include "PhysicsComponent.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"
#include "Collider.hpp"
#include "Timer.hpp"

const float Bullet::MAX_TTL = 5.0f;

Bullet::Bullet() : GameObject()
{
    name = "Bullet";
    damage = 10;
    speed = 500;
    ttl = MAX_TTL;

    //cache timer
    timer = Timer::instance();
}

Bullet::~Bullet()
{
    timer.reset();
    timer = nullptr;
}

void Bullet::update()
{
    float delta = timer->getDeltaTime();

    ttl -= delta;

    if(ttl < 0.0f) 
    {
        despawn();
    }


}

void Bullet::setDamage(int damage)
{
    this->damage = damage;
}

int Bullet::getDamage()
{
    return damage;
}

void Bullet::setSpeed(float speed)
{
    this->speed = speed;
}

float Bullet::getSpeed()
{
    return speed;
}


void Bullet::spawn(Vector3f& position, Vector3f& direction, float orientation)
{
    // TODO: might need to fix this - bullet will be inside of player?1
    this->getTransform()->getPosition()->assign(position);
    this->getTransform()->setAngle(orientation);

    std::shared_ptr<Vector3f> velocity = this->getPhysicsComponent()->getVelocity();

    // set velocity to direction of player
    velocity->assign(direction);

    // make unit length
    velocity->normalise();

    // scale by speed for velocity vector
    velocity->scale(speed);

    //this->getPhysicsComponent()->setVelocity(velocity);

    ttl = MAX_TTL;

    this->enable();

}

void Bullet::despawn()
{
    this->disable();
    ttl = -10.0f;
}

void Bullet::handleCollision(std::shared_ptr<Collider> other)
{
    despawn();
}
