#ifndef NPC_BULLET_MANAGER_HPP
#define NPC_BULLET_MANAGER_HPP

#include <vector>
#include <memory>

class Bullet;
class Vector3f;

class NPCBulletManager {

public:
    ~NPCBulletManager();

    void init(int maxObjects);

    void spawnBullet(Vector3f& position, Vector3f& direction, float orientation);

    static std::shared_ptr<NPCBulletManager> instance();

private:
    // Singleton - private constructor
    NPCBulletManager();
    
    int maxObjects;
    std::vector<std::shared_ptr<Bullet>> bullets;

    static std::shared_ptr<NPCBulletManager> gof;

    std::shared_ptr<Bullet> nextFree();

    static const int MAX_NPC_BULLETS = 100;
};

#endif