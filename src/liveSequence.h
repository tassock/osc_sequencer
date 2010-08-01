#ifndef _lIVE_SEQUENCE
#define _lIVE_SEQUENCE

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "liveSequenceSong.h"
#include "liveSequenceClip.h"
#include "sequencerApp.h"

#define NUM_S_TRACKS 2
#define NUM_S_SONGS 20

class liveSequenceSong;

class liveSequence {
	
public:
	liveSequence(sequencerApp* _sequencer, int _id);
	void loadSongs();
	void loadClips();
	int numSongsInTrack(int track_id);
	liveSequenceSong* getSongInTrack(int track_id, int song_order);
	string getName();
	liveSequenceSong* getSelectedSong();
	
	int id;
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	liveSequenceSong* songs[NUM_S_SONGS];
	int num_songs;
	string name;
	
};

#endif