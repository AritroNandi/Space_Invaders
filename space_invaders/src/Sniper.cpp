#include "Sniper.hpp"

Sniper::Sniper() {
    xPos  = MAX_X_POS / 2;
    yPos = 0;
    
    hitBox.x = xPos;
    hitBox.y = yPos;
    hitBox.width = myImage.getWidth();
    hitBox.height = myImage.getHeight();
    
    healthPoints = ENEMY_MAX_HEALTH;
}

int Sniper::getXPos() {
    return xPos;
}

int Sniper::getYPos() {
    return yPos;
}

int Sniper::getHealthPoints() {
    return healthPoints;
}

void Sniper::loseHealthPoints(bool playerHit) {
    if (playerHit) {
        healthPoints = 0;
    } else {
        healthPoints -= 1;
    }
}

bool Sniper::intersects(MainCharacter player) {
    if (player.hitBox.intersects(hitBox)) {
        return true;
    } else {
        return false;
    }
}

void Sniper::clearHitBox() {
    hitBox.width = 0;
    hitBox.height = 0;
}

void Sniper::move() {
    return;
}
