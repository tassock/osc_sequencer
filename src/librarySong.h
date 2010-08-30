#ifndef _LIBRARY_SONG
#define _LIBRARY_SONG

#include <string>
#include "ofxSQLiteHeaders.h"
#include "sequencerApp.h"
#include "clip.h"

class sequencerApp;
class clip;

class librarySong {
	
public:
	librarySong(sequencerApp* _sequencer, int _id);
	librarySong(sequencerApp* _sequencer, int _id, string _artist, string _title, int _bpm, int _key, int _major);
	void loadClips();
	string getName();
	string getLowercaseName();
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
	
};

#endif