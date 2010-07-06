#ifndef _lIVE_SEQUENCE
#define _lIVE_SEQUENCE

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "liveSequenceSong.h"
#include "liveSequenceClip.h"
#include "sequencerApp.h"

#define NUM_S_TRACKS 2
#define NUM_S_CLIPS 20
#define NUM_S_SONGS 20

class liveSequenceSong;
class liveSequenceClip;

class liveSequence {
	
public:
	liveSequence(sequencerApp* _sequencer, int _id);
	void loadSongs();
	void loadClips();
	int numSongsInTrack(int track_id);
	liveSequenceSong* getSongInTrack(int track_id, int song_order);
	int numClipsInTrack(int track_id);
	liveSequenceClip* getClipInTrack(int track_id, int clip_order);
	string getName();
	
	int id;
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	liveSequenceSong* songs[NUM_S_SONGS];
	liveSequenceClip* clips[NUM_S_CLIPS];
	int num_songs;
	int num_clips;
	string name;
	
};

#endif