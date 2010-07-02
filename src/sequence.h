#ifndef _SEQUENCE
#define _SEQUENCE

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "sequencerTrack.h"

#define NUM_TRACKS 2

class sequence {
	
public:
	sequence();
	
	sequencerTrack* tracks[NUM_TRACKS];
	
};

#endif