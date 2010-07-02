#ifndef _LIVE_SEQUENCE_TRACK
#define _LIVE_SEQUENCE_TRACK

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "liveSequenceClip.h"

#define NUM_S_CLIPS 10

class liveSequenceTrack {
	
public:
	liveSequenceTrack();
	liveSequenceClip* getClip(int i);
	
	liveSequenceClip* clips[NUM_S_CLIPS];
	
};

#endif