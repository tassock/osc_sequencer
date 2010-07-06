#ifndef _LIBRARY_SONG
#define _LIBRARY_SONG

#include <string>
#include "ofxSQLiteHeaders.h"
#include "sequencerApp.h"

class librarySong {
	
public:
	librarySong(sequencerApp* _sequencer, int _id);
	string getName();
	
	sequencerApp* sequencer;
	int id;
	string artist;
	string title;
	int bpm;
	int key;
	bool major;
	
};

#endif