#include "BulletManager.hpp"
#include "GameObjectFactory.hpp"
#include "Bullet.hpp"

#include <iostream>

BulletManager::BulletManager()
{
	maxBullets = 20;
}

BulletManager::~BulletManager()
{
	std::vector<std::shared_ptr<Bullet>>::iterator itt;
	for (itt = bullets.begin(); itt != bullets.end(); itt++)
		(*itt).reset(); // call reset on shared pointer

	bullets.clear();
}

void BulletManager::init(int maxBullets)
{
	bullets.resize(maxBullets);

	std::vector<std::shared_ptr<Bullet>>::iterator itt;
	for (itt = bullets.begin(); itt != bullets.end(); itt++)
	{
		(*itt) = GameObjectFactory::instance()->createBullet();
		(*itt)->disable();
	}
}

void BulletManager::spawnBullet(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction, float orientation)
{
	std::shared_ptr<Bullet> bullet = this->nextFree();

	if (bullet != nullptr)
	{
		bullet->spawn(position, direction, orientation);
		std::cout << "Bullet manager spawning" << std::endl;
	}
	else
	{
		std::cout << "Bullet manager has no bullets" << std::endl;
	}

}

std::shared_ptr<Bullet> BulletManager::nextFree()
{
	std::vector<std::shared_ptr<Bullet>>::iterator itt;
	for (itt = bullets.begin(); itt != bullets.end(); ++itt)
	{
		//std::shared_ptr<Bullet> temp = *itt;
		if ((*itt)->isEnabled() == false)
			return (*itt);
	}
	
	return nullptr;
}
