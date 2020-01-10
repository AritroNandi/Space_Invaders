#include "Bullet.hpp"

Bullet::Bullet(Enemy* shooter) {
    startXPos = shooter -> xPos;
    startYPos = shooter -> yPos;
    
    currXPos = startXPos;
    currYPos = startYPos;
    
    hitBox.x = startXPos;
    hitBox.y = startYPos;
    hitBox.width = BULLET_HIT_BOX_WIDTH;
    hitBox.height = BULLET_HIT_BOX_HEIGHT;
}

Bullet::Bullet(MainCharacter shooter) {
    startXPos = shooter.getXPos();
    startYPos = shooter.getYPos();
    
    currXPos = startXPos;
    currYPos = startYPos;
    
    hitBox.x = startXPos;
    hitBox.y = startYPos;
    hitBox.width = BULLET_HIT_BOX_WIDTH;
    hitBox.height = BULLET_HIT_BOX_HEIGHT;
}

void Bullet::move() {
    if (startYPos == 0) {
        if (startXPos == 0) {
            currXPos += MOVE_DIST;
            currYPos += MOVE_DIST;
            
            hitBox.x += MOVE_DIST;
            hitBox.y += MOVE_DIST;
            return;
        }
        if (startXPos == MAX_X_POS - 10) {
            currXPos -= MOVE_DIST;
            currYPos += MOVE_DIST;
            
            hitBox.x -= MOVE_DIST;
            hitBox.y += MOVE_DIST;
            return;
        }
        currYPos += MOVE_DIST;
        hitBox.y += MOVE_DIST;
    } else {
        currYPos -= MOVE_DIST;
        hitBox.y -= MOVE_DIST;
    }
}

int Bullet::getStartXPos() {
    return startXPos;
}

int Bullet::getStartYPos() {
    return startYPos;
}

int Bullet::getXPos() {
    return currXPos;
}

int Bullet::getYPos() {
    return currYPos;
}

void Bullet::clearHitBox() {
    hitBox.width = 0;
    hitBox.height = 0;
}

bool Bullet::intersects(MainCharacter player) {
    if (hitBox.intersects(player.hitBox)) {
        return true;
    } else {
        return false;
    }
}

bool Bullet::intersects(Enemy* e) {
    if (hitBox.intersects(e -> hitBox)) {
        return true;
    } else {
        return false;
    }
}
