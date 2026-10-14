#include "Collider.hpp"

Collider::Collider()
{
    radius = 0.0f;
    resolution = false;
}

Collider::Collider(float rad, bool flag, std::shared_ptr<GameObject> gameObject) : Component(gameObject), radius(radius), resolution(resolution)
{

}

Collider::~Collider()
{
}

float Collider::getRadius()
{
    return radius;
}

void Collider::setRadius(float rad)
{
    radius = rad;
}

bool Collider::needsResolution()
{
    return resolution;
}

void Collider::setResolution(bool flag)
{
    resolution = flag;
}
