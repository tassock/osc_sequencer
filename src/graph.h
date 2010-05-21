#ifndef _GRAPH
#define _GRAPH

#include <string>
#include "ofMain.h"
#include "sequencerApp.h"

#define NUM_BEATS 4
#define NUM_STEPS 32

class sequencerApp;

class graph {
	
	public:
		graph(int _x, int _y, int _w, int _h, sequencerApp* _sequencer);
		void draw();
		void drawAxis(string marker, int height, int x, int y);
		void mousePressed(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
		void mouseReleased();
		int mouseStep();
		void editStep();
		void setHighlightStart();
		void setHighlightEnd();
	
		void keyPressed  (int key);
		void keyReleased  (int key);
		
		ofTrueTypeFont TTF;
		
		sequencerApp *sequencer;
		
		int selectedBeat;
		int selectedStep;
		
		int graphX;
		int graphY;
		int graphW;
		int graphH;
		int graphColW;
		int graphColPad;
		int graphBeats;
		
		string cursorMode;
		int highlightStart;
		int highlightEnd;
		float stepClipBoard[NUM_BEATS * NUM_STEPS];
	
};

#endif	