#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "GameObject.hpp"

class BulletManager;
class Vector3f;
class Timer;

class Player : public GameObject {

public:
    Player();
    ~Player();

    void init(int maxBullets);

    void update();

    void setSpeed(float speed);
    float getSpeed();
    void takeDamage(int damage);

    void handleCollision(std::shared_ptr<Collider> other);

    static const int MAX_HP = 100;
    static const int MAX_BULLETS = 50;
private:
    float speed;
    float fireCooldown;
    bool canFire;
    int hp;
    std::shared_ptr<BulletManager> bulletManager;
    std::shared_ptr<Timer> timer;

    static const float FIRE_RATE;
};

#endif