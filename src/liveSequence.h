#ifndef _lIVE_SEQUENCE
#define _lIVE_SEQUENCE

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "liveSequenceClip.h"

#define NUM_S_TRACKS 2
#define NUM_S_CLIPS 20

class liveSequence {
	
public:
	liveSequence(ofxSQLite* _sqlite, int _id);
	void loadClips();
	int numClipsInTrack(int track_id);
	liveSequenceClip* getClipInTrack(int track_id, int clip_order);
	string getName();
	
	int id;
	ofxSQLite* sqlite;
	liveSequenceClip* clips[NUM_S_CLIPS];
	int num_clips;
	string name;
	
};

#endif