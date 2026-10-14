#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class BulletManager;

class Player : public GameObject {

private:
	float speed;
	std::shared_ptr<BulletManager> bulletManager;
public:
	Player();
	virtual ~Player();
	 
	void setSpeed(float s);
	float getSpeed();

	void init();
	void update();

	void handleCollision(std::shared_ptr<Collider> other);
};

#endif