#ifndef _LIVE_SEQUENCER_SONG
#define _LIVE_SEQUENCER_SONG

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "clip.h"
#include "librarySong.h"
#include "liveClip.h"
#include "sequencerApp.h"

class librarySong;

class liveSequenceSong {
	
public:
	liveSequenceSong(sequencerApp* _sequencer, int _id, int _song_id, int _track_id, int _bar_start, int _length);
	int getTrackId();
	string getName();
	int  getStart();
	void setStart(int bar);
	int getEnd();
	int getLength();
	
	sequencerApp* sequencer;
	int id;
	int song_id;
	int track_id;
	int bar_start;
	int length;
	string name;
	librarySong* library_song;
};

#endif