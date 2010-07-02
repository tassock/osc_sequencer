#ifndef _SEQUENCER_CLIP
#define _SEQUENCER_TRACK

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"

class sequencerClip {
	
public:
	sequencerClip(int _start, int _end);
	
	int start;
	int end;
	
};

#endif