//
//  MainCharacter.cpp
//  space_invaders
//
//  Created by Aritro Nandi on 1/9/20.
//

#include "MainCharacter.hpp"

MainCharacter::MainCharacter() {
    xPos = START_X_POS;
    yPos = START_Y_POS;
    healthPoints = MAX_HEALTH;
    hitBox.x = xPos;
    hitBox.y = yPos;
}

int subtractPosition(int position) {
    int copyPosition = position;
    int newPosition = position - MOVE_DIST;
    
    if (newPosition <= 0) {
        copyPosition = 0;
    } else {
        copyPosition = newPosition;
    }
    
    return copyPosition;
}

int addPosition(int position, bool x) {
    int copyPosition = position;
    int newPosition = position + MOVE_DIST;
    
    int maxPosition;
    
    if (x) {
        maxPosition = MAX_X_POS;
    } else {
        maxPosition = MAX_Y_POS;
    }
    
    if (newPosition >= maxPosition) {
        copyPosition = maxPosition;
    } else {
        copyPosition = newPosition;
    }
    
    return copyPosition;
}

void MainCharacter::move(Direction directionToMove) {
    if (directionToMove == Direction::UP) {
        yPos = subtractPosition(yPos);
        hitBox.y = yPos;
        return;
    }
    
    if (directionToMove == Direction::LEFT) {
        xPos = subtractPosition(xPos);
        hitBox.x = xPos;
        return;
    }
    
    if (directionToMove == Direction::DOWN) {
        yPos = addPosition(yPos, false);
        hitBox.y = yPos;
        return;
    }
    
    if (directionToMove == Direction::RIGHT) {
        xPos = addPosition(xPos, true);
        hitBox.x = xPos;
        return;
    }
}

int MainCharacter::getXPos() {
    return xPos;
}
int MainCharacter::getYPos() {
    return yPos;
}
int MainCharacter::getHealthPoints() {
    return healthPoints;
}

void MainCharacter::loseHealth(bool enemyContact) {
    if (enemyContact == true) {
        healthPoints -= ENEMY_HEALTH;
    } else {
        healthPoints -= 1;
    }
}
