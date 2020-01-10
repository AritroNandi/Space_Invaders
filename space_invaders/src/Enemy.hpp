#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "MainCharacter.hpp"

const int ENEMY_MAX_HEALTH = 20;

struct Enemy {
    int xPos;
    int yPos;
    int healthPoints;
    
    ofImage myImage;
    ofRectangle hitBox;
    
    virtual void move() = 0;
    virtual bool intersects(MainCharacter player) = 0;
    virtual void loseHealthPoints(bool playerHit) = 0;
    virtual void clearHitBox() = 0;
};
