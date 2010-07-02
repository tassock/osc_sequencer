#ifndef _SEQUENCER_APP
#define _SEQUENCER_APP

#include "clip.h"
#include "pattern.h"
#include "param.h"
#include "slider.h"
#include "graph.h"
#include "liveSequenceWindow.h"

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxAbleton.h"
#include "ofxXmlSettings.h"
#include "ofxSQLiteHeaders.h"

//#define HOST "169.254.189.237"
#define HOST "localhost"
//#define SEND_PORT 12345
//#define RECIEVE_PORT 7403

#define NUM_BEATS 4
#define NUM_STEPS 32
#define NUM_PATTERNS 3
#define NUM_PARAMS 9
#define NUM_CLIPS 2

class graph;

//--------------------------------------------------------
class sequencerApp : public ofBaseApp{

	public:
	
		sequencerApp();
	
		void initDatabase();

		void setup();
		void update();
		void draw();
	
		void drawRenderWindow();
		void drawClipNav();
		void drawPatternNav();
		void drawParamNav();
		void drawNavigationItem(int x, int y, string name, bool selected);
		
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		int  mouseStep();
		bool mouseInside(int x, int y, int width, int height);
		void setSelected();
		void setSelectedParamsAndPatterns();
		void setGainSliderValue();
		void setScaleSliderValue();
		void resetSelectValues();

		void keyPressed  (int key);
		void keyReleased  (int key);
		
		// Accessors
		param * getSParam();
		int getBeat();
		int getStep();
		int getMouseX();
		int getMouseY();

  
		ofxSQLite* sqlite;
		liveSet* current_set;
		liveSequenceWindow* sequence_window;
		ofTrueTypeFont TTF;
	
		string xmlStructure;
		string message;

	private:

		ofxOscSender sender;
		ofxOscReceiver *receiver;
	
		param *connection;
		graph *main_graph;
	
		int beat;
		int step;
		int selectedClip;
		int selectedPattern;
		int selectedParam;
	
		clip *sClip;
		pattern *sPattern;
		param * sParam;
	
		string renderMode;
		string cursorMode;
		int highlightStart;
		int highlightEnd;
		float stepClipBoard[NUM_BEATS * NUM_STEPS];
	
		clip *clipBuffer[NUM_CLIPS];
	
	
		slider *gainSlider;
		slider *scaleSlider;
		float gainSliderValue;
		float scaleSliderValue;
	
		int windowW;
		int windowH;
		
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
	
		int rWindowX;
		int rWindowY;
		int rWindowH;
		int rWindowW;
	
		int sWindowX;
		int sWindowY;
		int sWindowW;
		int sWindowH;

};

#endif
