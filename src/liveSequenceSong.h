#ifndef _LIVE_SEQUENCER_SONG
#define _LIVE_SEQUENCER_SONG

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "clip.h"
#include "librarySong.h"
#include "liveClip.h"
#include "sequencerApp.h"
#include "liveSequenceClip.h"

class librarySong;
class liveSequenceClip;

class liveSequenceSong {
	
public:
	liveSequenceSong(sequencerApp* _sequencer, int _id, int _song_id, int _track_id, int _bar_start, int _length);
	void save();
	void loadClips();
	vector<liveSequenceClip*> getClips();
	liveSequenceClip* getClip(int index);
	int getNumClips();
	liveSequenceClip* removeClip(liveSequenceClip* delete_clip);
	liveSequenceClip* duplicateClip(liveSequenceClip* duplicate_clip);
	int getId();
	int getTrackId();
	void setTrackId(int _track_id);
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
	vector<liveSequenceClip*> clips;
};

#endif