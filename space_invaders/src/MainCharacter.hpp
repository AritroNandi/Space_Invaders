#pragma once

#include <stdio.h>
#include "ofMain.h"

using std::string;

const int START_X_POS = 270;
const int START_Y_POS = 570;
const int MAX_X_POS = 540;
const int MAX_Y_POS = 590;
const int MAX_HEALTH = 100;
const int MOVE_DIST = 30;
const int ENEMY_HEALTH = 20;

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class MainCharacter {
    private:
        int xPos;
        int yPos;
        int healthPoints;
    public:
        MainCharacter();
        
        ofImage myImage;
        ofRectangle hitBox;
        
        int getXPos();
        int getYPos();
        int getHealthPoints();
        
        void move(Direction directionToMove);
        
        void loseHealth(bool enemyContact);
};
