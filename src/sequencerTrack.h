#ifndef _SEQUENCER_TRACK
#define _SEQUENCER_TRACK

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "sequencerClip.h"

#define NUM_CLIPS 10

class sequencerTrack {
	
public:
	sequencerTrack();
	
	sequencerClip* clips[NUM_CLIPS];
	
};

#endif