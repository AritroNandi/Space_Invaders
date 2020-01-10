//
//  Sniper.hpp
//  space_invaders
//
//  Created by Aritro Nandi on 1/9/20.
//

#pragma once

#include <stdio.h>
#include "Enemy.hpp"

class Sniper : public Enemy {
    public:
        Sniper();
        
        int getHealthPoints();
        int getXPos();
        int getYPos();
    
        void move();
        bool intersects(MainCharacter player);
        void loseHealthPoints(bool playerHit);
    
        void clearHitBox();
};
