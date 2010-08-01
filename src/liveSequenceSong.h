#ifndef _LIVE_SEQUENCER_SONG
#define _LIVE_SEQUENCER_SONG

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "clip.h"
#include "librarySong.h"
#include "liveClip.h"
#include "sequencerApp.h"
#include "liveSequenceClip.h"

#define NUM_S_CLIPS 20

class librarySong;
class liveSequenceClip;

class liveSequenceSong {
	
public:
	liveSequenceSong(sequencerApp* _sequencer, int _id, int _song_id, int _track_id, int _bar_start, int _length);
	void loadClips();
	liveSequenceClip* getClip(int index);
	int getNumClips();
	int getTrackId();
	string getName();
	int  getStart();
	void setStart(int bar);
	int getEnd();
	int getLength();
	
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	int id;
	int song_id;
	int track_id;
	int bar_start;
	int length;
	string name;
	librarySong* library_song;
	
	int num_clips;
	liveSequenceClip* clips[NUM_S_CLIPS];
};

#endif