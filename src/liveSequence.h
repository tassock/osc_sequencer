#ifndef _lIVE_SEQUENCE
#define _lIVE_SEQUENCE

#include <string>

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "liveSequenceSong.h"
#include "liveSequenceClip.h"
#include "sequencerApp.h"

#define NUM_S_TRACKS 2

class liveSequenceSong;
class liveSequenceClip;

class liveSequence {
	
public:
	liveSequence(sequencerApp* _sequencer, int _id);
	void loadSongs();
	void loadClips();
	vector<liveSequenceSong*> getSongs();
	vector<liveSequenceSong*> getTrackSongs(int track_id);
	vector<liveSequenceClip*> getTrackClips(int track_id);
	int getClipOrder(liveSequenceClip* l_clip);
	string getName();
	void selectPosition(char direction);
	
	int id;
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	
	vector<liveSequenceSong*> songs;
	vector<liveSequenceClip*> clips;
	string name;
	
	string select_mode;
	
};

#endif