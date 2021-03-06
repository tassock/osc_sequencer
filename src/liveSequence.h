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
class librarySong;

class liveSequence {
	
public:
	liveSequence(sequencerApp* _sequencer, int _id);
	void save();
	void loadSongs();
	void loadClips();
	vector<liveSequenceSong*> getSongs();
	vector<liveSequenceSong*> getTrackSongs(int track_id);
	vector<liveSequenceClip*> getTrackClips(int track_id);
	liveSequenceClip* getNearestClip(int track_id, int bar);
	int getClipOrder(liveSequenceClip* l_clip);
	int nextSongStart(int track_id, int bar);
	int prevSongEnd(int track_id, int bar);
	string getName();
	void selectPosition(char direction);
	liveSequenceSong* addLibrarySong(librarySong* song, int track_id, int bar);
	
	int id;
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	
	vector<liveSequenceSong*> songs;
	vector<liveSequenceClip*> clips;
	string name;
	
	string select_mode;
	
};

#endif