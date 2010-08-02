#ifndef _LIVE_SEQUENCER_CLIP
#define _LIVE_SEQUENCER_CLIP

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "clip.h"
#include "liveClip.h"
#include "sequencerApp.h"
#include "liveSequenceSong.h"

class sequencerApp;
class liveSequenceSong;

class liveSequenceClip {
	
public:
	liveSequenceClip(sequencerApp* _sequencer, liveSequenceSong* _song, int _id, int _clip_id, int _track_id, int _bar_start, int _length);
	liveClip* getLiveClip();
	liveSequenceSong* getSong();
	int getTrackId();
	string getName();
	int getStart();
	int getEnd();
	int getLength();
	
	sequencerApp* sequencer;
	liveSequenceSong* song;
	ofxSQLite* sqlite;
	clip* library_clip;
	liveClip* live_clip;
	int id;
	int clip_id;
	int track_id;
	int bar_start;
	int length;
	string name;
	
};

#endif