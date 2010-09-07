#ifndef _LIBRARY_SONG_BROWSER
#define _LIBRARY_SONG_BROWSER

#include "sequencerApp.h"
#include "librarySong.h"

class librarySong;

class librarySongBrowser {
	
public:
	librarySongBrowser(sequencerApp* _sequencer);
	void loadSongBuffer();
	void draw();
	void keyPressed(int key);
	
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	
	vector<librarySong*> song_buffer;
	string query;
	int select_index;
	
	int browserX;
	int browserY;
	int browserH;
	int browserW;
	
	ofTrueTypeFont  franklinBook;

};

#endif