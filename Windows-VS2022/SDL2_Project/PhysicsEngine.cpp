#include "PhysicsEngine.hpp"

#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"

PhysicsEngine::PhysicsEngine()
{
	maxObjects = 0;
}

PhysicsEngine::~PhysicsEngine()
{
	std::vector<std::shared_ptr<PhysicsComponent>>::iterator itt;
	for (itt = bodies.begin(); itt != bodies.end(); itt++)
		(*itt).reset(); // call reset on shared pointer

	bodies.clear();
}

void PhysicsEngine::addPhysicsComponent(std::shared_ptr<PhysicsComponent> newComponent)
{
	bodies.push_back(newComponent);
}


void PhysicsEngine::init(int maxObjects)
{
	bodies.resize(maxObjects);
}

bool PhysicsEngine::removePhysicsComponent(std::shared_ptr<PhysicsComponent> oldComponent)
{
	bool deleted = false;
	std::vector<std::shared_ptr<PhysicsComponent>>::iterator itt;
	for (itt = bodies.begin(); itt != bodies.end(); itt++)
	{
		std::shared_ptr<PhysicsComponent> temp = *itt;
		if (temp == oldComponent)
		{
			bodies.erase(itt);
			deleted = true;
			// itt - now invalid as we have altered the vector
			break;
		}
	}

	return deleted;
}

void PhysicsEngine::update(float dt)
{
	std::shared_ptr<PhysicsComponent> body;
	std::shared_ptr<GameObject> object;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<Vector3f> position;
	std::shared_ptr<Vector3f> velocity;

	std::vector<std::shared_ptr<PhysicsComponent>>::iterator itt;
	for (itt = bodies.begin(); itt != bodies.end(); itt++)
	{
		body = *itt;

		if (body == nullptr)
			continue;

		object = body->getGameObject();

		if (object->isEnabled() == false)
			continue;

		transform = object->getTransform();
		position = transform->getPosition();
		velocity = body->getVelocity();

		// copy velocity and scale
		Vector3f movement(*velocity);
		movement.scale(dt);

		// add to position
		position->add(movement);
	}
}