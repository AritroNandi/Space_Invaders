//
//  Zagger.cpp
//  space_invaders
//
//  Created by Aritro Nandi on 1/9/20.
//

#include "Zagger.hpp"

Zagger::Zagger(bool setSpawnAtRight) {
    spawnAtRight = setSpawnAtRight;
    if (setSpawnAtRight) {
        xPos = MAX_X_POS - 10;
        yPos = 0;
    } else {
        xPos = 0;
        yPos = 0;
    }
    
    hitBox.x = xPos;
    hitBox.y = yPos;
    hitBox.width = myImage.getWidth();
    hitBox.height = myImage.getHeight();
    
    healthPoints = ENEMY_MAX_HEALTH;
}

int Zagger::getXPos() {
    return xPos;
}

int Zagger::getYPos() {
    return yPos;
}

int Zagger::getHealthPoints() {
    return healthPoints;
}

void Zagger::move() {
    if (spawnAtRight) {
        xPos -= MOVE_DIST;
        yPos += MOVE_DIST;
    } else {
        xPos += MOVE_DIST;
        yPos += MOVE_DIST;
    }
    
    if (yPos == MAX_Y_POS / 2) {
        changeDirection();
        myImage = counterpart;
    }
}

void Zagger::changeDirection() {
    spawnAtRight = !spawnAtRight;
}

void Zagger::loseHealthPoints(bool playerHit) {
    if (playerHit) {
        healthPoints = 0;
    } else {
        healthPoints -= 1;
    }
}

bool Zagger::intersects(MainCharacter player) {
    if (player.hitBox.intersects(hitBox)) {
        return true;
    } else {
        return false;
    }
}

void Zagger::clearHitBox() {
    hitBox.width = 0;
    hitBox.height = 0;
}
