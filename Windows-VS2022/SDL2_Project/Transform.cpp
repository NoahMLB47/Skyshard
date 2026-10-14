#include "Transform.hpp"

Transform::Transform()
{
    position = nullptr;
    scale = nullptr;
    angle = 0.0f;
}

Transform::~Transform()
{
}

float Transform::getAngle()
{
    return 0.0f;
}

std::shared_ptr<Vector3f> Transform::getPosition()
{
    return position;
}

std::shared_ptr<Vector3f> Transform::getScale()
{
    return scale;
}

void Transform::setAngle(float a)
{
    angle = a;
}

void Transform::setPosition(std::shared_ptr<Vector3f> p)
{
    position = p;
}

void Transform::setScale(std::shared_ptr<Vector3f> s)
{
    scale = s;
}
