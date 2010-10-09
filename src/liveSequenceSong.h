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
	liveSequenceSong(sequencerApp* _sequencer, librarySong* song, int _track_id, int _bar_start, int _sequence_id);
	void save();
	void loadClips();
	vector<liveSequenceClip*> getClips();
	liveSequenceClip* getClip(int index);
	int getNumClips();
	liveSequenceClip* removeClip(liveSequenceClip* delete_clip);
	liveSequenceClip* duplicateClip(liveSequenceClip* duplicate_clip);
	void insertClip(clip* _insert_clip, int _order);
	int getId();
	int getTrackId();
	void setTrackId(int _track_id);
	string getName();
	int  getStart();
	void setStart(int bar);
	int getEnd();
	int getLength();
	librarySong* getLibrarySong();
	void draw(int songX, int songY, string select_mode, liveSequenceSong* selected_song, liveSequenceClip* selected_clip);
	string stringWithinWidth(string input, int length);
	
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	int id;
	int song_id;
	int track_id;
	int bar_start;
	int length;
	int sequence_id;
	string name;
	librarySong* library_song;
	
	int num_clips;
	vector<liveSequenceClip*> clips;
	vector<liveSequenceClip*> deleted_clips;
	
	ofTrueTypeFont  franklinBook;
};

#endif