//
//  Zagger.hpp
//  space_invaders
//
//  Created by Aritro Nandi on 1/9/20.
//

#pragma once

#include <stdio.h>
#include "Enemy.hpp"

class Zagger : public Enemy {
    private:
        bool spawnAtRight;
    public:
        Zagger(bool setSpawnAtRight);
        
        int getHealthPoints();
        int getXPos();
        int getYPos();
        
        void changeDirection();
        
        ofImage counterpart;
        
        void move();
        bool intersects(MainCharacter player);
        
        void loseHealthPoints(bool playerHit);
        void clearHitBox();
};
