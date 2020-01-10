#include "ofMain.h"
#include "SpaceInvadersGame.h"

//========================================================================
int main( ){
    ofSetupOpenGL(DEFAULT_WINDOW_WIDTH,DEFAULT_WINDOW_HEIGHT,OF_WINDOW);            // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new SpaceInvadersGame());
}
