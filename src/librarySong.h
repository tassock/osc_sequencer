#ifndef _LIBRARY_SONG
#define _LIBRARY_SONG

#include <string>
#include "ofxSQLiteHeaders.h"
#include "sequencerApp.h"
#include "clip.h"

class sequencerApp;
class clip;
class liveSequenceSong;

class librarySong {
	
public:
	librarySong(sequencerApp* _sequencer, int _id);
	librarySong(sequencerApp* _sequencer, int _id, string _artist, string _title, int _bpm, int _key, int _major);
	void loadClips();
	void loadSequenceSongs();
	vector<liveSequenceSong*> getSequenceSongs();
	string getName();
	string getLowercaseName();
	int getId();
	vector<clip*> getClips();
	clip* getClip(int index);
	
	sequencerApp* sequencer;
	int id;
	string artist;
	string title;
	int bpm;
	int key;
	bool major;
	vector<clip*> clips;
	vector<liveSequenceSong*> sequence_songs;
	
};

#endif