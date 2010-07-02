#ifndef _LIVE_SEQUENCER_CLIP
#define _LIVE_SEQUENCER_CLIP

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"

class liveSequenceClip {
	
public:
	liveSequenceClip(int _start, int _end);
	int getStart();
	int getEnd();
	int getLength();
	
	int start;
	int end;
	
};

#endif