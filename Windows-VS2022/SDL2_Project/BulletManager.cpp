#include "BulletManager.hpp"

#include "Bullet.hpp"
#include "GameObject.hpp"
#include "Vector3f.hpp"
#include "GameObjectFactory.hpp"

BulletManager::BulletManager()
{
    maxObjects = 20;
}

BulletManager::~BulletManager()
{
    std::vector<std::shared_ptr<Bullet>>::iterator itt;
    for(itt = bullets.begin(); itt != bullets.end(); ++itt)
    {
        (*itt).reset(); // call reset on the shared pointer!
    }
    
    bullets.clear();
}

void BulletManager::init(int maxObjects)
{
    bullets.resize(maxObjects);

    // create bullets - using factory
    std::vector<std::shared_ptr<Bullet>>::iterator itt;
    for(itt = bullets.begin(); itt != bullets.end(); ++itt)
    {
         (*itt) = GameObjectFactory::instance()->createBullet("playerBullet");
         (*itt)->disable();
    }

}

void BulletManager::spawnBullet(Vector3f& position, Vector3f& direction, float orientation)
{
    std::shared_ptr<Bullet> bullet = this->nextFree();

    if(bullet != nullptr)
    {   
        bullet->spawn(position, direction, orientation);
       // std::cout << "Bullet manager spawning" << std::endl;
    }
    else 
    {
       // std::cout << "Bullet manager has no bullets" << std::endl;
    }

    // if no bullets just ignore?
}

std::shared_ptr<Bullet> BulletManager::nextFree()
{
    std::vector<std::shared_ptr<Bullet>>::iterator itt;
    for(itt = bullets.begin(); itt != bullets.end(); ++itt)
    {
        std::shared_ptr<Bullet> temp = *itt;
        if((*itt)->isEnabled() == false)
            return (*itt);
    }

    return nullptr;
}
