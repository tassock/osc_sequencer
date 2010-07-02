#ifndef _lIVE_SEQUENCE
#define _lIVE_SEQUENCE

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "liveSequenceTrack.h"

#define NUM_S_TRACKS 2

class liveSequence {
	
public:
	liveSequence();
	string getName();
	liveSequenceTrack * getTrack(int i);
	
	liveSequenceTrack* tracks[NUM_S_TRACKS];
	string name;
	
};

#endif