#pragma once

#include <stdio.h>
#include "Enemy.hpp"

const int BULLET_HIT_BOX_WIDTH = 10;
const int BULLET_HIT_BOX_HEIGHT = 10;

class Bullet {
    private:
        int startXPos;
        int startYPos;
        int currXPos;
        int currYPos;
    public:
        Bullet(Enemy* shooter);
        Bullet(MainCharacter shooter);
        
        ofRectangle hitBox;
        
        int getXPos();
        int getYPos();
        int getStartXPos();
        int getStartYPos();
        
        void clearHitBox();
        
        bool intersects(MainCharacter player);
        bool intersects(Enemy* e);
        
        void move();
};
