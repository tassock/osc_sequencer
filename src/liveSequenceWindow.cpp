#include "liveSequenceWindow.h"

liveSequenceWindow::liveSequenceWindow(ofxSQLite* _sqlite, int _x, int _y, int _w, int _h) {
	sqlite = _sqlite;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	sequence = new liveSequence(sqlite, 1);
}

void liveSequenceWindow::draw() {
	
	// Background
	ofRect(x, y, w, h);
	
	// Sequencer vars
	int beatHeight = 20;
	int padding = 5;
	
	
	// Track vars
	int trackX = 0;
	int trackY = y + 20;
	int trackW = 200;
	int trackH = 400;
	
	// Clip vars
	int clipX = 0;
	int clipY = 0;
	int clipW = 200;
	int clipH = 0;
	
	// Draw tracks
	for(int t = 0; t < NUM_S_TRACKS; t++){
		ofSetColor(128, 128, 128);
		trackX = x + padding + (t * (trackW + padding));
		ofRect(trackX, trackY, trackW, trackH);
		
		// DrawClips
		for(int c = 0; c < sequence->numClipsInTrack(t); c++) { // find number of clips in track
			ofSetColor(0, 128, 128);
			liveSequenceClip* s_clip = sequence->getClipInTrack(t, c);
			clipX = trackX;
			clipY = trackY + (s_clip->getStart() * beatHeight);
			clipH = s_clip->getLength() * beatHeight;
			ofRect(clipX, clipY, clipW, clipH);
		}
	}
}