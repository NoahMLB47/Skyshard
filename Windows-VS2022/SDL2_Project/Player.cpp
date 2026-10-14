#include "Player.hpp"
#include "InputManager.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Collider.hpp"
#include "BulletManager.hpp"

Player::Player() : GameObject()
{
	speed = 300.0f;
	name = "Player";
}

Player::~Player()
{

}

void Player::setSpeed(float s)
{
	speed = s;
}

float Player::getSpeed()
{
	return speed;
}

void Player::init()
{
	bulletManager = std::shared_ptr<BulletManager>(new BulletManager());
	bulletManager->init(20);
}

void Player::update()
{
	float horizontal = InputManager::instance()->getHorizontalInput();
	float vertical = InputManager::instance()->getVerticalInput();

	std::shared_ptr<Vector3f> velocity = physicsComponent->getVelocity();
	
	velocity->setX(horizontal);
	velocity->setY(vertical);

	// normalise

	// scale by speed
	velocity->scale(speed);

	// No need to do a set - accessing the velocity directly
}

void Player::handleCollision(std::shared_ptr<Collider> other)
{
}
