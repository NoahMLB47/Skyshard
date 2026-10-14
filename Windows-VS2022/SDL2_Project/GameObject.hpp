#pragma once

#include <memory>
#include <string>

class Transform;
class Sprite;
class PhysicsComponent;
class Collider;

class GameObject {

protected:
	std::shared_ptr<Transform> transform;
	std::shared_ptr<Sprite> sprite;
	std::shared_ptr<PhysicsComponent> physicsComponent;
	std::string name;
	std::shared_ptr<Collider> collider;
	bool enabled;

public:
	GameObject();
	virtual ~GameObject();

	std::shared_ptr<Transform> getTransform();
	void setTransform(std::shared_ptr<Transform> t);

	std::shared_ptr<Sprite> getSprite();
	void setSprite(std::shared_ptr<Sprite> s);

	void setName(std::string n);
	std::string getName();

	void setPhysicsComponent(std::shared_ptr<PhysicsComponent> component);
	std::shared_ptr<PhysicsComponent> getPhysicsComponent();

	void setCollider(std::shared_ptr<Collider> coll);
	std::shared_ptr<Collider> getCollider();

	void enable();
	void disable();

	bool isEnabled();

	virtual void update() = 0;

	virtual void handleCollision(std::shared_ptr<Collider> other) = 0;
};