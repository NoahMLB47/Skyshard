#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

class Vector3f {

private:
	float x;
	float y;
	float z;

public:
	Vector3f();
	Vector3f(float x, float y, float z);
	~Vector3f();
	
	void setX(float newX);
	void setY(float newY);
	void setZ(float newZ);

	float getX();
	float getY();
	float getZ();		

	void scale(float scalingFactor);
	void add(Vector3f& other);
	void subtract(Vector3f& other);

	float getLength();
	void normalise();
};

#endif