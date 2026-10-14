#ifndef COLLISIONENGINE_HPP
#define COLLISIONENGINE_HPP

#include <memory>
#include <vector>

class Collider;

class CollisionEngine {

private:
	std::vector<std::shared_ptr<Collider>> colliders;
	int maxObjects;

public:
	CollisionEngine();
	~CollisionEngine();
	
	void init(int maxObjects);
	void addCollider(std::shared_ptr<Collider> coll);
	bool removeCollider(std::shared_ptr<Collider> coll);
	void check();
	bool collide(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b);
	void handleCollision(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b);
	void resolveCollision(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b);
};

#endif