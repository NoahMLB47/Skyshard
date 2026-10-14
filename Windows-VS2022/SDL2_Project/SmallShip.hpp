#ifndef SMALL_SHIP_HPP
#define SMALL_SHIP_HPP

#include "NPC.hpp"

class SmallShip : public NPC {

public:
    SmallShip();
    ~SmallShip();

    void update();
    void init();
    void ai();
    void takeDamage(int damage);
private:

    const int MAX_HP = 30;
    const int SCORE_POINTS = 20;
    const float FIRE_RATE = 1.0f;
};

#endif