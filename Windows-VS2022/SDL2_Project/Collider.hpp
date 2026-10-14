#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "Component.hpp"

class Collider : public Component {

private:
	float radius;
	bool resolution;

public:
	Collider();
	Collider(float rad, bool flag, std::shared_ptr<GameObject> gameObject);
	~Collider();
	
	float getRadius();
	void setRadius(float rad);
	bool needsResolution();
	void setResolution(bool flag);
};

#endif