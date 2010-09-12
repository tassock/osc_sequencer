#ifndef _LIBRARY_SONG_BROWSER
#define _LIBRARY_SONG_BROWSER

#include "sequencerApp.h"
#include "librarySong.h"

class librarySong;

class librarySongBrowser {
	
public:
	librarySongBrowser(sequencerApp* _sequencer);
	void loadSongBuffer();
	void updateQueryBuffer();
	void draw();
	void keyPressed(int key);
	string getView();
	librarySong* getSelectedSong();
	
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	
	vector<librarySong*> song_buffer;
	vector<librarySong*> query_buffer;
	string query;
	string view;
	int select_index;
	
	int browserX;
	int browserY;
	int browserH;
	int browserW;
	
	ofTrueTypeFont  franklinBook;

};

#endif