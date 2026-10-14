#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <memory>
#include <vector>

class PhysicsComponent;

class PhysicsEngine {

private:
	int maxObjects;

	std::vector<std::shared_ptr<PhysicsComponent>> bodies;
public:
	PhysicsEngine();
	~PhysicsEngine();

	void update(float dt);

	void addPhysicsComponent(std::shared_ptr<PhysicsComponent> component);
	bool removePhysicsComponent(std::shared_ptr<PhysicsComponent> oldComponent);

	void init(int maxObjects);
};

#endif