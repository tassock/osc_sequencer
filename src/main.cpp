//#include "ofMain.h"
//#include "sequencerApp.h"
//#include "ofAppGlutWindow.h"
//
////========================================================================
//int main( ){
//
//    ofAppGlutWindow window;
//	ofSetupOpenGL(&window, 1060,820, OF_WINDOW);			// <-------- setup the GL context
//	
//	ofSetVerticalSync(true);
//	ofEnableAlphaBlending();
//	//ofSetFrameRate(64);
//
//	// this kicks off the running of my app
//	// can be OF_WINDOW or OF_FULLSCREEN
//	// pass in width and height too:
//	ofRunApp( new sequencerApp());
//
//}


#include "ofMain.h"
#include "sequencerApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
	
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1060,820, OF_WINDOW);			// <-------- setup the GL context
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	
	sequencerApp* app = new sequencerApp;
	
	ofxFenster fenster;
	fenster.init(app);
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( app );
	
}
