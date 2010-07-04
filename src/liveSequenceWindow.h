#ifndef _lIVE_SEQUENCE_WINDOW
#define _lIVE_SEQUENCE_WINDOW

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "liveSequence.h"

#define NUM_S_TRACKS 2

class liveSequenceWindow {
	
public:
	liveSequenceWindow(ofxSQLite* _sqlite, int _x, int _y, int _w, int _h);
	void draw();
	
	liveSequence* sequence;
	ofxSQLite* sqlite;
	int x;
	int y;
	int w;
	int h;
	
};

#endif