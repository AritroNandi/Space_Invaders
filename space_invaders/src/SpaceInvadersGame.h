#pragma once

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "ofMain.h"
#include "ofxVectorGraphics.h"
#include "Zagger.hpp"
#include "Sniper.hpp"
#include "Liner.hpp"
#include "Bullet.hpp"

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::cin;
using std::endl;

enum class GameState {
    FIRST_RUN, IN_PROGRESS, FINISHED
};

const int DEFAULT_WINDOW_WIDTH = 600;
const int DEFAULT_WINDOW_HEIGHT = 650;
const int POSSIBLE_ENEMY_X_START_POSITIONS [] = {0, MAX_X_POS / 4, MAX_X_POS / 2, (3 * MAX_X_POS) / 4, MAX_X_POS - 10};
const string SCORE_FILE = "/Users/gurgenz221/of_v0.11.0_osx_release/apps/myApps/space_invaders/bin/data/scores.txt";
const int INITIAL_FIRE_RATE = 10;

class SpaceInvadersGame : public ofBaseApp {
	public:
		ofImage background;
        ofImage mainCharacterImage;
        ofImage zaggerRightImage;
        ofImage zaggerLeftImage;
        ofImage sniperImage;
        ofImage linerImage;
        
        GameState currGameState;
        
        MainCharacter mainCharacter;
        
        ofxVectorGraphics output;
    
        string userName;
    
        int round;
        int fireRate;
        int score;
    
        vector<Bullet> bulletsOnScreen;
        vector<Enemy*> enemiesOnScreen;
        
        void initializeBookKeeper();
        void updateBookKeeper();
        map<int, int> bookKeeper;
    
        void respawn();
        void initializeHitBox(Enemy* enemy);
        Enemy* determineWhatRespawns(int positionToRespawnIn);
    
        void enemiesFire();
    
        void setup();
    
        void update();
        void updateSprites();
    
        void checkForCollisions();
    
        void draw();
    
        void drawRound();
        void drawStart();
        void drawIfFinished();
        void drawBullets();
        void drawHealth();
        void drawScore();
        void drawEnemies();
    
        void keyPressed(int key);
    
        void storeUserName();
};
