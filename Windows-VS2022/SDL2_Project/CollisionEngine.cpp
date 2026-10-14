#include "CollisionEngine.hpp"
#include "Vector3f.hpp"
#include "Collider.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

#include <memory>
#include <cmath>
#include <iostream>

CollisionEngine::CollisionEngine()
{
	maxObjects = 0;
}

CollisionEngine::~CollisionEngine()
{
	std::vector<std::shared_ptr<Collider>>::iterator itt;
	for (itt = colliders.begin(); itt != colliders.end(); itt++)
		(*itt).reset(); // call reset on shared pointer

	colliders.clear();
}

void CollisionEngine::init(int maxObjects)
{
	colliders.resize(maxObjects);
}

void CollisionEngine::addCollider(std::shared_ptr<Collider> coll)
{
	colliders.push_back(coll);
}

bool CollisionEngine::removeCollider(std::shared_ptr<Collider> coll)
{
	bool deleted = false;
	std::vector<std::shared_ptr<Collider>>::iterator itt;
	for (itt = colliders.begin(); itt != colliders.end(); itt++)
	{
		std::shared_ptr<Collider> temp = *itt;
		if (temp == coll)
		{
			colliders.erase(itt);
			deleted = true;
			// itt - now invalid as we have altered the vector
			break;
		}
	}

	return deleted;
}

void CollisionEngine::check()
{
	std::shared_ptr<Collider> colliderOne;

	std::vector<std::shared_ptr<Collider>>::iterator itt;
	for (itt = colliders.begin(); itt != colliders.end(); itt++)
	{
		colliderOne = *itt;

		if (colliderOne == nullptr)
			continue;

		if (colliderOne->getGameObject()->isEnabled() == false)
			continue;

		std::shared_ptr<Collider> colliderTwo;


		std::vector<std::shared_ptr<Collider>>::iterator itt2;
		for (itt2 = colliders.begin(); itt2 != colliders.end(); itt2++)
		{
			colliderTwo = *itt2;

			if (colliderTwo == nullptr)
				continue;

			if (colliderTwo->getGameObject()->isEnabled() == false)
				continue;
			
			if (colliderOne == colliderTwo)
				continue;

			// Collision check
			if (collide(colliderOne, colliderTwo) == true)
			{
				// Handle collision
				handleCollision(colliderOne, colliderTwo);
			}

		}
	}
}

bool CollisionEngine::collide(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b)
{
	std::shared_ptr<Vector3f> posA;
	std::shared_ptr<Vector3f> posB;
	std::shared_ptr<Vector3f> s;

	float radiusA;
	float radiusB;

	posA = a->getGameObject()->getTransform()->getPosition();
	posB = b->getGameObject()->getTransform()->getPosition();

	radiusA = a->getRadius();
	radiusB = b->getRadius();

	s.reset(new Vector3f(posA->getX(), posA->getY(), posA->getZ()));
	s->subtract(*posB.get());

	float sLength = s->getLength();

	if (sLength < (radiusA + radiusB))
		return true;
	else
		return false;
}

void CollisionEngine::handleCollision(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b)
{
	bool resolve = a->needsResolution() && b->needsResolution();

	if (resolve == true)
	{
		resolveCollision(a, b);
	}

	// inform objects

	a->getGameObject()->handleCollision(b);
	b->getGameObject()->handleCollision(a);
}

void CollisionEngine::resolveCollision(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b)
{
	float touchingDistance;
	float actualDistance;

	std::shared_ptr<Vector3f> posA;
	std::shared_ptr<Vector3f> posB;

	posA = a->getGameObject()->getTransform()->getPosition();
	posB = b->getGameObject()->getTransform()->getPosition();

	// get vector between a and b

	Vector3f delta(*posB.get());
	delta.subtract(*posA.get());

	// calculate actual distance

	actualDistance = delta.getLength();

	// make this a direction

	delta.normalise();

	// calculate the touching distance
	touchingDistance = a->getRadius() + b->getRadius();

	// scale the correction
	delta.scale((touchingDistance - actualDistance)/2.0f);

	// fix this for a
	posA->subtract(delta);

	// fix this for b
	posB->add(delta);
}
