#ifndef _TEST_APP
#define _TEST_APP

#include "clip.h"
#include "pattern.h"
#include "param.h"
#include "slider.h"

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofxSQLiteHeaders.h"

#define HOST "localhost"
#define SEND_PORT 12345
#define RECIEVE_PORT 7403

#define NUM_BEATS 4
#define NUM_STEPS 32
#define NUM_PATTERNS 3
#define NUM_PARAMS 9
#define NUM_CLIPS 2

//--------------------------------------------------------
class testApp : public ofBaseApp{

	public:
	
		void initDatabase();

		void setup();
		void update();
		void draw();
	
		void drawGraph();
		void drawSliders();
		void drawClipNav();
		void drawPatternNav();
		void drawParamNav();
		void drawNavigationItem(int x, int y, string name, bool selected);
		void drawAxis(string marker, int height, int x, int y);
		
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		bool mouseInside(int x, int y, int width, int height);
		void setSelected();
		void setSelectedParamsAndPatterns();
		void setGainSliderValue();
		void setScaleSliderValue();
		void resetSelectValues();

		void keyPressed  (int key);

		ofxXmlSettings XML;
		ofxSQLite* sqlite;
		ofTrueTypeFont TTF;
	
		string xmlStructure;
		string message;

	private:

		ofxOscSender sender;
		ofxOscReceiver	receiver;
	
		param *connection;
	
		int beat;
		int step;
		int selectedBeat;
		int selectedStep;
		int selectedPattern;
		int selectedParam;
	
		clip *sClip;
		pattern *sPattern;
		pattern *sSavedPattern; // not sure I need this
		param * sParam;
		param * sSavedParam; // not sure I need this
	
		pattern *patternBuffer[NUM_PATTERNS];
		pattern *savedPatterns[NUM_PATTERNS];
	
		clip *clipBuffer[NUM_CLIPS];
	
	
		slider *gainSlider;
		slider *scaleSlider;
		float gainSliderValue;
		float scaleSliderValue;
		
		int graphX;
		int graphY;
		int graphW;
		int graphH;
		int graphColW;
		int graphColPad;
		int graphBeats;
	
		int navItemW;
		int navItemH;
		int navItemXPad;
		int navItemYPad;
	
		int clipNavX;
		int clipNavY;
		int clipNavW;
		int clipNavH;
	
		int patternNavX;
		int patternNavY;
		int patternNavW;
		int patternNavH;
		
		int paramNavX;
		int paramNavY;
		int paramNavW;
		int paramNavH;

};

#endif
