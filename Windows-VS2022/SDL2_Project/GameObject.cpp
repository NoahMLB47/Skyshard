#include "GameObject.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Collider.hpp"

GameObject::GameObject()
{
    transform = nullptr;
    sprite = nullptr;
    enabled = false;
}

GameObject::~GameObject()
{
    transform.reset();
    transform = nullptr;
    sprite.reset();
    sprite = nullptr;
}

std::shared_ptr<Transform> GameObject::getTransform()
{
    return transform;
}

void GameObject::setTransform(std::shared_ptr<Transform> t)
{
    transform = t;
}

std::shared_ptr<Sprite> GameObject::getSprite()
{
    return sprite;
}

void GameObject::setSprite(std::shared_ptr<Sprite> s)
{
    sprite = s;
}

void GameObject::setName(std::string n)
{
    name = n;
}

std::string GameObject::getName()
{
    return name;
}

void GameObject::setPhysicsComponent(std::shared_ptr<PhysicsComponent> component)
{
    physicsComponent = component;
}

std::shared_ptr<PhysicsComponent> GameObject::getPhysicsComponent()
{
    return physicsComponent;
}

void GameObject::setCollider(std::shared_ptr<Collider> coll)
{
    collider = coll;
}

std::shared_ptr<Collider> GameObject::getCollider()
{
    return collider;
}

void GameObject::enable()
{
    enabled = true;
}

void GameObject::disable()
{
    enabled = false;
}

bool GameObject::isEnabled()
{
    return enabled;
}
