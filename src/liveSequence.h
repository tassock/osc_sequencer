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
//	int numSongsInTrack(int track_id);
//	liveSequenceSong* getSongInTrack(int track_id, int song_order);
	vector<liveSequenceSong*> getTrackSongs(int track_id);
	vector<liveSequenceClip*> getTrackClips(int track_id);
	string getName();
	liveSequenceSong* getSelectedSong();
	liveSequenceClip* getSelectedClip();
	void selectPosition(char direction);
	
	int id;
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	
	//liveSequenceSong* songs[NUM_S_SONGS];
	vector<liveSequenceSong*> songs;
	// liveSequenceSong* clips[NUM_S_SONGS];
	vector<liveSequenceClip*> clips;
	liveSequenceSong* selected_song;
	liveSequenceClip* selected_clip;
	string name;
	
	string select_mode;
	
};

#endif