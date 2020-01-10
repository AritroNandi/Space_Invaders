#include "SpaceInvadersGame.h"

//--------------------------------------------------------------
void SpaceInvadersGame::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    background.load("/Users/gurgenz221/of_v0.11.0_osx_release/apps/myApps/space_invaders/bin/data/space.jpg");
    mainCharacterImage.load("/Users/gurgenz221/of_v0.11.0_osx_release/apps/myApps/space_invaders/bin/data/space_ship.PNG");
    zaggerRightImage.load("/Users/gurgenz221/of_v0.11.0_osx_release/apps/myApps/space_invaders/bin/data/zagger_right.png");
    zaggerLeftImage.load("/Users/gurgenz221/of_v0.11.0_osx_release/apps/myApps/space_invaders/bin/data/zagger_left.png");
    sniperImage.load("/Users/gurgenz221/of_v0.11.0_osx_release/apps/myApps/space_invaders/bin/data/sniper.png");
    linerImage.load("/Users/gurgenz221/of_v0.11.0_osx_release/apps/myApps/space_invaders/bin/data/liner.png");
    
    mainCharacter = MainCharacter();
    mainCharacter.myImage = mainCharacterImage;
    mainCharacter.hitBox.width = mainCharacterImage.getWidth();
    mainCharacter.hitBox.height = mainCharacterImage.getHeight();
    
    Zagger* rightZagger = new Zagger(true);
    rightZagger -> myImage = zaggerRightImage;
    rightZagger -> counterpart = zaggerLeftImage;
    rightZagger -> hitBox.width = zaggerRightImage.getWidth();
    rightZagger -> hitBox.height = zaggerRightImage.getHeight();
    
    Zagger* leftZagger = new Zagger(false);
    leftZagger -> myImage = zaggerLeftImage;
    leftZagger -> counterpart = zaggerRightImage;
    leftZagger -> hitBox.width = zaggerLeftImage.getWidth();
    leftZagger -> hitBox.height = zaggerLeftImage.getHeight();
    
    Liner* rightLiner = new Liner(true);
    rightLiner -> myImage = linerImage;
    rightLiner -> hitBox.width = linerImage.getWidth();
    rightLiner -> hitBox.height = linerImage.getHeight();
    
    Liner* leftLiner = new Liner(false);
    leftLiner -> myImage = linerImage;
    leftLiner -> hitBox.width = linerImage.getWidth();
    leftLiner -> hitBox.height = linerImage.getHeight();
    
    Sniper* sniper = new Sniper();
    sniper -> myImage = sniperImage;
    sniper -> hitBox.width = sniperImage.getWidth();
    sniper -> hitBox.height = sniperImage.getHeight();
    
    currGameState = GameState::FIRST_RUN;
    ofResetElapsedTimeCounter();
    round = 1;
    fireRate = INITIAL_FIRE_RATE;
    
    enemiesOnScreen.push_back(rightZagger);
    enemiesOnScreen.push_back(leftZagger);
    enemiesOnScreen.push_back(rightLiner);
    enemiesOnScreen.push_back(leftLiner);
    enemiesOnScreen.push_back(sniper);
    
    initializeBookKeeper();
}

void SpaceInvadersGame::initializeBookKeeper() {
    for (int i = 0; i < 5; ++i) {
        bookKeeper[POSSIBLE_ENEMY_X_START_POSITIONS[i]] = 1;
    }
}

void SpaceInvadersGame::updateBookKeeper() {
    for (int i = 0; i < 5; ++i) {
        bookKeeper[POSSIBLE_ENEMY_X_START_POSITIONS[i]] = 0;
        
        for (Enemy* e: enemiesOnScreen) {
            if (e -> xPos == bookKeeper[POSSIBLE_ENEMY_X_START_POSITIONS[i]] && e -> yPos == 0) {
                bookKeeper[POSSIBLE_ENEMY_X_START_POSITIONS[i]] = 1;
            }
        }
    }
}

void SpaceInvadersGame::respawn() {
    for (int i = 0; i < 5; ++i) {
        int key = POSSIBLE_ENEMY_X_START_POSITIONS[i];
        
        if (bookKeeper[key] == 0) {
            enemiesOnScreen.push_back(determineWhatRespawns(key));
        }
    }
}

void SpaceInvadersGame::initializeHitBox(Enemy* enemy) {
    if (enemy -> xPos == 0 || enemy -> xPos == MAX_X_POS - 10) {
        enemy -> hitBox.width = zaggerRightImage.getWidth();
        enemy -> hitBox.height = zaggerRightImage.getHeight();
    } else if (enemy -> xPos == MAX_X_POS / 2) {
        enemy -> hitBox.width = sniperImage.getWidth();
        enemy -> hitBox.height = sniperImage.getHeight();
    } else if (enemy -> xPos == (3 * MAX_X_POS) / 4 || enemy -> xPos == (MAX_X_POS / 4)) {
        enemy -> hitBox.width = linerImage.getWidth();
        enemy -> hitBox.height = linerImage.getHeight();
    } else {
        return;
    }
}

Enemy* SpaceInvadersGame::determineWhatRespawns(int positionToRespawnIn) {
    if (positionToRespawnIn == POSSIBLE_ENEMY_X_START_POSITIONS[0]) {
        Zagger* zaggerToAdd = new Zagger(false);
        zaggerToAdd -> myImage = zaggerLeftImage;
        zaggerToAdd -> counterpart = zaggerRightImage;
        
        initializeHitBox(zaggerToAdd);
        
        return zaggerToAdd;
    } else if (positionToRespawnIn == POSSIBLE_ENEMY_X_START_POSITIONS[1]) {
        Liner* linerToAdd = new Liner(false);
        linerToAdd -> myImage = linerImage;
        
        initializeHitBox(linerToAdd);
        
        return linerToAdd;
    } else if (positionToRespawnIn == POSSIBLE_ENEMY_X_START_POSITIONS[2]) {
        Sniper* sniperToAdd = new Sniper();
        sniperToAdd -> myImage = sniperImage;
        
        initializeHitBox(sniperToAdd);
        
        return sniperToAdd;
    } else if (positionToRespawnIn == POSSIBLE_ENEMY_X_START_POSITIONS[3]) {
        Liner* linerToAdd = new Liner(true);
        linerToAdd -> myImage = linerImage;
        
        initializeHitBox(linerToAdd);
        
        return linerToAdd;
    } else {
        Zagger* zaggerToAdd = new Zagger(true);
        zaggerToAdd -> myImage = zaggerRightImage;
        zaggerToAdd -> counterpart = zaggerLeftImage;
        
        initializeHitBox(zaggerToAdd);
        
        return zaggerToAdd;
    }
}

void SpaceInvadersGame::enemiesFire() {
    for (Enemy* e : enemiesOnScreen) {
        if (e -> yPos == 0) {
            Bullet enemyBullet = Bullet(e);
            bulletsOnScreen.push_back(enemyBullet);
        }
    }
}

void SpaceInvadersGame::drawHealth() {
    string hp = "HP:";
    ofDrawBitmapString(hp, 0, DEFAULT_WINDOW_HEIGHT - 20);
    
    output.disableCenterRect();
    output.setColor(255, 79, 79);
    output.rect(25, DEFAULT_WINDOW_HEIGHT - 30, mainCharacter.getHealthPoints(), 10);
    output.endShape();
    output.setColor(255, 255, 255);
}

void SpaceInvadersGame::drawScore() {
    string scoreMessage = "SCORE: ";
    scoreMessage += std::to_string(score);
    
    ofDrawBitmapString(scoreMessage, 0, DEFAULT_WINDOW_HEIGHT - 35);
}

void SpaceInvadersGame::drawRound() {
    string roundMessage = "ROUND ";
    roundMessage += std::to_string(round);
    ofDrawBitmapString(roundMessage, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void SpaceInvadersGame::drawStart() {
    background.draw(0,0);
    mainCharacterImage.draw(START_X_POS, START_Y_POS);
    drawRound();
    drawScore();
    drawHealth();
    drawEnemies();
}

void SpaceInvadersGame::drawBullets() {
    for (Bullet b: bulletsOnScreen) {
        ofDrawRectangle(b.hitBox);
    }
}

void SpaceInvadersGame::drawEnemies() {
    for (Enemy* e: enemiesOnScreen) {
        e -> myImage.draw(e -> xPos, e -> yPos);
    }
}

void SpaceInvadersGame::storeUserName() {
    string scoreAsString = to_string(score);
    
    std::fstream scoreFileStream;
    scoreFileStream.open(SCORE_FILE, std::fstream::in | std::fstream::out | std::fstream::ate);
    
    scoreFileStream << "\n" << userName << "--" << scoreAsString << endl;
    scoreFileStream.close();
}

void SpaceInvadersGame::drawIfFinished() {
    background.draw(0,0);
    ofSetColor(255, 255, 255);
    
    string deathMessage = "YOU HAVE DIED. YOU HAVE EARNED: ";
    deathMessage += to_string(score);
    deathMessage += " POINTS";
    
    string enterScoreMessage = "TYPE KEYS TO ENTER YOUR NAME. PRESS RETURN WHEN YOU'RE DONE.";
    string nameMessage = "NAME: ";
    nameMessage += userName;
    
    ofDrawBitmapString(deathMessage, 150, (ofGetWindowHeight() / 2) - 15);
    ofDrawBitmapString(enterScoreMessage, 100, (ofGetWindowHeight() / 2) + 15);
    ofDrawBitmapString(nameMessage, 150, (ofGetWindowHeight() / 2) + 45);
}

void SpaceInvadersGame::updateSprites() {
    for (int i = 0; i < bulletsOnScreen.size(); ++i) {
        bool offScreen = bulletsOnScreen[i].getXPos() < 0 || bulletsOnScreen[i].getXPos() > MAX_X_POS || bulletsOnScreen[i].getYPos() < 0 || bulletsOnScreen[i].getYPos() > MAX_Y_POS;
        
        if (offScreen) {
            bulletsOnScreen.erase(bulletsOnScreen.begin() + i);
        } else {
            bulletsOnScreen[i].move();
        }
    }
    
    for (int i = 0; i < enemiesOnScreen.size(); ++i) {
        bool offScreen = enemiesOnScreen[i] -> xPos < 0 || enemiesOnScreen[i] -> xPos > MAX_X_POS ||
        enemiesOnScreen[i] -> yPos < 0 || enemiesOnScreen[i] -> yPos > MAX_Y_POS;
        
        if (offScreen) {
            enemiesOnScreen.erase(enemiesOnScreen.begin() + i);
        }
        if (enemiesOnScreen[i] -> healthPoints <= 0) {
            score += round * ENEMY_HEALTH;
            enemiesOnScreen.erase(enemiesOnScreen.begin() + i);
        }
        if (enemiesOnScreen[i] -> healthPoints < ENEMY_MAX_HEALTH) {
            enemiesOnScreen[i] -> move();
        }
    }
}

void SpaceInvadersGame::checkForCollisions() {
    for (Bullet b: bulletsOnScreen) {
        if (b.intersects(mainCharacter) && (b.getStartXPos() != mainCharacter.getXPos()) && (b.getStartYPos() != mainCharacter.getYPos())) {
            mainCharacter.loseHealth(false);
            b.clearHitBox();
        }
        
        for (Enemy* e: enemiesOnScreen) {
            if (b.intersects(e) && (b.getStartXPos() != e -> xPos) && (b.getStartYPos() != e -> yPos)) {
                e -> loseHealthPoints(false);
            }
        }
    }
    
    for (Enemy* e: enemiesOnScreen) {
        if (e -> intersects(mainCharacter)) {
            mainCharacter.loseHealth(true);
            e -> loseHealthPoints(true);
            e -> clearHitBox();
        }
    }
}

//--------------------------------------------------------------
void SpaceInvadersGame::update(){
    if (currGameState == GameState::FINISHED) {
        return;
    }
    
    int elapsedTimeAsInt = (int) ofGetElapsedTimef();
    int timeInterval = 30;
    int respawnRate = 6;
    int roundWhenFireRateShouldIncrease = 5;
    int minFireRate = 2;
    
    if (elapsedTimeAsInt != 0 && ((elapsedTimeAsInt % timeInterval) == 0)) {
        ++round;
        
        if (fireRate - 1 >= minFireRate && (round % roundWhenFireRateShouldIncrease == 0)) {
           --fireRate;
        }
        ofResetElapsedTimeCounter();
    }
    
    if (currGameState == GameState::IN_PROGRESS) {
        if ((elapsedTimeAsInt % respawnRate) == 0) {
            respawn();
        }
        if ((elapsedTimeAsInt % fireRate) == 0) {
            enemiesFire();
        }
        checkForCollisions();
        updateSprites();
        updateBookKeeper();
    }
    
    if (mainCharacter.getHealthPoints() <= 0) {
        currGameState = GameState::FINISHED;
    }
}

//--------------------------------------------------------------
void SpaceInvadersGame::draw(){
    if (currGameState == GameState::FIRST_RUN) {
        drawStart();
        drawBullets();
        currGameState = GameState::IN_PROGRESS;
    } else if (currGameState == GameState::IN_PROGRESS) {
        background.draw(0,0);
        drawRound();
        drawScore();
        drawHealth();
        drawEnemies();
        drawBullets();
        mainCharacterImage.draw(mainCharacter.getXPos(), mainCharacter.getYPos());
    } else {
        drawIfFinished();
        return;
    }
}

//--------------------------------------------------------------
void SpaceInvadersGame::keyPressed(int key){
    int upperKey = toupper(key);
    
    if (currGameState == GameState::FINISHED) {
        if (key == OF_KEY_RETURN) {
            storeUserName();
            OF_EXIT_APP(0);
        }
        if (upperKey <= 90 && upperKey >= 65) {
            userName += (char) upperKey;
        }
    }
    
    if (upperKey == 'S') {
        Bullet bulletShot = Bullet(mainCharacter);
        bulletsOnScreen.push_back(bulletShot);
    }
    if (key == OF_KEY_LEFT) {
        mainCharacter.move(Direction::LEFT);
    }
    if (key == OF_KEY_RIGHT) {
        mainCharacter.move(Direction::RIGHT);
    }
    if (key == OF_KEY_UP) {
        mainCharacter.move(Direction::UP);
    }
    if (key == OF_KEY_DOWN) {
        mainCharacter.move(Direction::DOWN);
    }
}

