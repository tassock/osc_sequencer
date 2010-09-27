#ifndef _lIVE_SEQUENCE_WINDOW
#define _lIVE_SEQUENCE_WINDOW

#include <string>
#include "ofMain.h"
#include "liveSequence.h"
#include "liveSequenceSong.h"
#include "liveSequenceClip.h"
#include "sequencerApp.h"
#include "librarySong.h"
#include "librarySongBrowser.h"
#include "liveAutoLane.h"
#include "liveSequenceScale.h"
#include "liveUi.h"

#define NUM_S_TRACKS 2

class liveSequence;
class liveSequenceSong;
class liveSequenceClip;
class sequencerApp;
class librarySong;
class librarySongBrowser;
class liveAutoLane;
class liveSequenceScale;

class liveSequenceWindow: public liveUi {
	
public:
	liveSequenceWindow(sequencerApp* _sequencer, int _x, int _y, int _w, int _h);
	void update(int beat, int step);
	void draw(int beat, int step);
	void drawBrowser();
	void drawClipBrowser();
	void keyPressed(int key);
	void sequenceKeyPressed(int key);
	void clipBrowserKeyPressed(int key);
	void toggleSelectMode();
	void fireClips(int beat, int step);
	void mousePressed(int _x, int _y, int button);
	void mouseDragged(int _x, int _y, int button);
	void mouseReleased();
	
	liveSequence* sequence;
	sequencerApp* sequencer;
	ofxSQLite* sqlite;
	librarySongBrowser* song_browser;
	
	liveSequenceSong* selected_song;
	liveSequenceClip* selected_clip;
	int browserX;
	int browserY;
	int browserH;
	int browserW;
	int clip_select_index;
	string select_mode;
	string focus;
	vector<clip*> clip_buffer;
	
	ofTrueTypeFont  franklinBook;
	
	liveAutoLane* lane;
	liveSequenceScale* scale;
	
};

#endif