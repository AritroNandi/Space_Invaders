#pragma once

#include <stdio.h>
#include "Enemy.hpp"

class Liner : public Enemy {
    private:
        bool spawnAtRight;
    public:
        Liner(bool setSpawnAtRight);
        
        int getHealthPoints();
        int getXPos();
        int getYPos();
        
        void move();
        bool intersects(MainCharacter player);
        void loseHealthPoints(bool playerHit);
        
        void clearHitBox();
};
