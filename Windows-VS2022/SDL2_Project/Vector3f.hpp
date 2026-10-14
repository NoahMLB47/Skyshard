#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

#include <memory>

class Vector3f {

public:
    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f(Vector3f& other);
    Vector3f(std::shared_ptr<Vector3f> other);
    ~Vector3f();

    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);

    float getX();
    float getY();
    float getZ();

    void scale(float scalingFactor);

    void add(Vector3f& other);
    void add(std::shared_ptr<Vector3f> other);

    void sub(Vector3f& other);
    void sub(std::shared_ptr<Vector3f> other);

    void operator=(Vector3f& other);
    void operator=(std::shared_ptr<Vector3f> other);

    float getLength();
    void normalise();

    void rotate2D(float rads);

    void assign(Vector3f& other);
    void assign(std::shared_ptr<Vector3f> other);

private:
    float x;
    float y;
    float z;
};

#endif