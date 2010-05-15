#include "ofMain.h"
#include "sequencerApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1060,480, OF_WINDOW);			// <-------- setup the GL context
	
	//ofSetVerticalSync(true);
	ofSetFrameRate(64);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new sequencerApp());

}
