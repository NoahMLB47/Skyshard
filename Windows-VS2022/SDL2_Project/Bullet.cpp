#include "Bullet.hpp"
#include "Transform.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Collider.hpp"
#include "Timer.hpp"

const float Bullet::MAX_TTL = 10.0f;

Bullet::Bullet()
{
	name = "Bullet";
	damage = 10;
	speed = 100.0f;
	ttl = MAX_TTL;
	timer = Timer::instance();
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	float deltaTime = timer->getDeltaTime();

	ttl -= deltaTime;

	if (ttl < 0)
	{
		despawn();
	}
}

void Bullet::setDamage(int newDamage)
{
	damage = newDamage;
}

int Bullet::getDamage()
{
	return damage;
}

void Bullet::setSpeed(float s)
{
	speed = s;
}

float Bullet::getSpeed()
{
	return speed;
}

void Bullet::spawn(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction, float orientation)
{
	// TODO: bullet might be in player
	this->getTransform()->setPosition(position);

	std::shared_ptr<Vector3f> velocity = this->getPhysicsComponent()->getVelocity();

	// set velocity to direction of player
	velocity->setX(direction->getX());
	velocity->setY(direction->getY());
	velocity->setZ(direction->getZ());

	// make unit length
	velocity->normalise();

	// scale by speed for velocity vector
	velocity->scale(speed);

	this->getPhysicsComponent()->setVelocity(velocity);

	ttl = MAX_TTL;
}

void Bullet::despawn()
{
	this->disable();
	ttl = 0.0f;
}

void Bullet::handleCollision(std::shared_ptr<Collider> other)
{
	despawn();
}
