#ifndef _lIVE_SEQUENCE_WINDOW
#define _lIVE_SEQUENCE_WINDOW

#include <string>
#include "ofMain.h"
#include "liveSequence.h"
#include "liveSequenceSong.h"
#include "liveSequenceClip.h"
#include "sequencerApp.h"
#include "librarySong.h"

#define NUM_S_TRACKS 2

class liveSequence;
class liveSequenceSong;
class liveSequenceClip;
class sequencerApp;
class librarySong;

class liveSequenceWindow {
	
public:
	liveSequenceWindow(sequencerApp* _sequencer, int _x, int _y, int _w, int _h);
	void draw(int beat, int step);
	void drawBrowser();
	void loadSongBuffer();
	string stringWithinWidth(string input, int length);
	void keyPressed(int key);
	void toggleSelectMode();
	
	liveSequence* sequence;
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	liveSequenceSong* selected_song;
	liveSequenceClip* selected_clip;
	int x;
	int y;
	int w;
	int h;
	string select_mode;
	vector<librarySong*> song_buffer;
	
	ofTrueTypeFont  franklinBook;
	
};

#endif