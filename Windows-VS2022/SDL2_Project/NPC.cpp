#include "NPC.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Transform.hpp"

NPC::NPC()
{
    speed = 100.0f;
	name = "NPC";
}

NPC::~NPC()
{
}

void NPC::ai()
{
    // brittle
    std::shared_ptr<GameObject> player = Game::instance()->findGameObjectByName("Player");
    
    if (player != nullptr)
    {
        std::shared_ptr<Vector3f> playerPos = player->getTransform()->getPosition();

        std::shared_ptr<Vector3f> myPosition = transform->getPosition();
        std::shared_ptr<Vector3f> toPlayer(new Vector3f(*playerPos));

        toPlayer->subtract(*myPosition);
        toPlayer->normalise();
        toPlayer->scale(speed);

        physicsComponent->setVelocity(toPlayer);
    }
}

void NPC::update()
{
	ai();
}

void NPC::init()
{

}

void NPC::setSpeed(float s)
{
    speed = s;
}

float NPC::getSpeed()
{
    return speed;
}

void NPC::handleCollision(std::shared_ptr<Collider> other)
{
    speed = 0.0f;
}
