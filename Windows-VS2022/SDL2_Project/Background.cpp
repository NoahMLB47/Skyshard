#include "Background.hpp"
#include "Vector3f.hpp"
#include "PhysicsComponent.hpp"
#include "Transform.hpp"
#include "Window.hpp"

Background::Background() : GameObject()
{
    name = "background";
    speed = 500;
}

Background::~Background()
{
}

void Background::handleCollision(std::shared_ptr<Collider> other)
{
}

void Background::update()
{
    if (this->getTransform()->getPosition()->getX() <= -Window::WINDOW_WIDTH / 2.0f)
        this->getTransform()->getPosition()->setX((Window::WINDOW_WIDTH * 1.5f) - 10.0f);

}

void Background::init()
{
    // give background constant velocity
    std::shared_ptr<Vector3f> velocity = physicsComponent->getVelocity();
    velocity->setX(-1.0f);

    velocity->scale(speed);

}
