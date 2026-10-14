#ifndef NPC_HPP
#define NPC_HPP

#include "GameObject.hpp"

class NPC : public GameObject {

private:
	float speed;

public:
	NPC();
	~NPC();

	void ai();
	void update();
	void init();

	void setSpeed(float s);
	float getSpeed();

	void handleCollision(std::shared_ptr<Collider> other);
};

#endif