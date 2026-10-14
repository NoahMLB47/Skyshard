#ifndef BULLET_MANAGER_HPP
#define BULLET_MANAGER_HPP

#include <memory>
#include <vector>

class Vector3f;
class Bullet;
class GameObjectFactory;

class BulletManager {

private:
	int maxBullets;

	std::vector<std::shared_ptr<Bullet>> bullets;

	std::shared_ptr<Bullet> nextFree();
public:
	BulletManager();
	~BulletManager();

	void init(int maxBullets);
	void spawnBullet(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction, float orientation);
};

#endif