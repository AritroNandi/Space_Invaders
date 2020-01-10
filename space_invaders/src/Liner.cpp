#include "Liner.hpp"

Liner::Liner(bool setSpawnAtRight) {
    spawnAtRight = setSpawnAtRight;
    if (spawnAtRight) {
        xPos = (3 * MAX_X_POS) / 4;
        yPos = 0;
    } else {
        xPos = MAX_X_POS / 4;
        yPos = 0;
    }
    
    hitBox.x = xPos;
    hitBox.y = yPos;
    hitBox.height = myImage.getHeight();
    hitBox.width = myImage.getWidth();
    
    healthPoints = ENEMY_MAX_HEALTH;
}

int Liner::getXPos() {
    return xPos;
}

int Liner::getYPos() {
    return yPos;
}

int Liner::getHealthPoints() {
    return healthPoints;
}

void Liner::loseHealthPoints(bool playerHit) {
    if (playerHit) {
        healthPoints = 0;
    } else {
        healthPoints -= 1;
    }
}

bool Liner::intersects(MainCharacter player) {
    if (player.hitBox.intersects(hitBox)) {
        return true;
    } else {
        return false;
    }
}

void Liner::clearHitBox() {
    hitBox.width = 0;
    hitBox.height = 0;
}

void Liner::move() {
    yPos += 1;
    hitBox.y +=1;
}
