#ifndef _LIVE_SEQUENCER_CLIP
#define _LIVE_SEQUENCER_CLIP

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "clip.h"

class liveSequenceClip {
	
public:
	liveSequenceClip(ofxSQLite* _sqlite, int _id, int _clip_id, int _track_id, int _bar_start, int _length);
	int getTrackId();
	int getStart();
	int getEnd();
	int getLength();
	
	ofxSQLite* sqlite;
	clip* library_clip;
	int id;
	int clip_id;
	int track_id;
	int bar_start;
	int length;
	
};

#endif