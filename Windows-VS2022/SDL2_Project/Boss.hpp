#ifndef BOSS_HPP
#define BOSS_HPP

#include "NPC.hpp"

class Vector3f;

class Boss : public NPC {

public:
    Boss();
    ~Boss();

    void update();
    void init();
    void ai();
    void takeDamage(int damageDone);

private:
    std::shared_ptr<Vector3f> position;
    
    const int MAX_HP = 2000;
    const float FIRE_RATE = 0.5f;
};

#endif