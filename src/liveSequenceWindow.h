#ifndef _lIVE_SEQUENCE_WINDOW
#define _lIVE_SEQUENCE_WINDOW

#include <string>
#include "ofMain.h"
#include "liveSequence.h"
#include "sequencerApp.h"

#define NUM_S_TRACKS 2

class sequencerApp;
class liveSequence;

class liveSequenceWindow {
	
public:
	liveSequenceWindow(sequencerApp* _sequencer, int _x, int _y, int _w, int _h);
	void draw(int beat, int step);
	string stringWithinWidth(string input, int length);
	void keyPressed(int key);
	
	liveSequence* sequence;
	sequencerApp* sequencer;
	int x;
	int y;
	int w;
	int h;
	
	ofTrueTypeFont  franklinBook;
	
};

#endif