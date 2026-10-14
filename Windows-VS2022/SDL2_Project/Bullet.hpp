#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"

class Vector3f;
class Timer;

class Bullet : public GameObject {

private:
	int damage;
	float ttl;
	float speed;
	std::shared_ptr<Vector3f> position;
	std::shared_ptr<Vector3f> direction;
	std::shared_ptr<Timer> timer;

public:
	Bullet();
	~Bullet();

	void update();
	
	void setDamage(int newDamage);
	int getDamage();

	void setSpeed(float s);
	float getSpeed();
	
	void spawn(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction, float orientation);
	void despawn();

	void handleCollision(std::shared_ptr<Collider> other);

	static const float MAX_TTL;
};

#endif