//
// Created by rodian on 21/05/17.
//

#ifndef Z_TPGRUPAL_WEAPON_H
#define Z_TPGRUPAL_WEAPON_H

#include <iostream>
#include <vector>
#include "size.h"
#include "Occupant.h"
#include "bullet.h"

class Weapon {
private:
    std::string type;
    int damage, w_speed;
    bool explosive;
    Size w_size;
    std::vector<Bullet> bullets;

public:
    Weapon(std::string type, int damage, int w_speed, bool explosive,
                                                        Size w_size);

    void shotTarget(Occupant* target);

    bool isTheAttackExplosive();

    void checkIfBullestHit();
};


#endif //Z_TPGRUPAL_WEAPON_H
