#pragma once
#include "SDL2_Common.h"
#include <memory>

class Vector3f;

class Transform {

private:
	float angle;
	std::shared_ptr <Vector3f> position;
	std::shared_ptr <Vector3f> scale;

public:
	Transform();
	~Transform();

	float getAngle();
	std::shared_ptr<Vector3f> getPosition();
	std::shared_ptr<Vector3f> getScale();
	void setAngle(float a);
	void setPosition(std::shared_ptr<Vector3f> p);
	void setScale(std::shared_ptr<Vector3f> s);
};