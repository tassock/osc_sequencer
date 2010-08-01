#include "liveSequenceWindow.h"

liveSequenceWindow::liveSequenceWindow(sequencerApp* _sequencer, int _x, int _y, int _w, int _h) {
	sequencer = _sequencer;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	sequence = new liveSequence(sequencer, 1);
	
	select_mode = "song";
	
	franklinBook.loadFont("frabk.ttf", 12);
}

void liveSequenceWindow::draw(int beat, int step) {
	
	// Background
	ofRect(x, y, w, h);
	
	// Sequencer vars
	int beatHeight = 20;
	int padding = 5;
	
	// Track vars
	int trackX = 0;
	int trackY = y + 20;
	int trackW = 180;
	int trackH = 700;
	
	// Song vars
	int songX = 0;
	int songY = 0;
	int songW = 20;
	int songH = 0;
	
	// Clip vars
	int clipX = 0;
	int clipY = 0;
	int clipW = 160; 
	int clipH = 0;
	int clipP = 2;
	
	// Draw tracks
	for(int t = 0; t < NUM_S_TRACKS; t++){
		ofSetColor(128, 128, 128);
		trackX = x + padding + (t * (trackW + padding));
		ofRect(trackX, trackY, trackW, trackH);
		
		// Default Colors
		int orange = 0xFFA24F;
		int pink = 0xFA4FFF;
		int grey = 0xBDBDBD;
		int background_color = 0x000000;
		int color = 0; // dynamic
		
		// DrawSongs()
		vector<liveSequenceSong*> song_buffer = sequence->getTrackSongs(t);
		for(int c = 0; c < song_buffer.size(); c++) { // find number of songs in track
			liveSequenceSong* s_song = song_buffer[c];
			songX = trackX;
			songY = trackY + (s_song->getStart() * beatHeight) - (beat * beatHeight) - (step * beatHeight / 32);
			songH = s_song->getLength() * beatHeight;
			
			// Color
			if (select_mode == "song" and s_song == sequence->getSelectedSong() ) {
				color = orange;
			} else {
				color = grey;
			}
			
			// Vertical song name
			ofSetColor(0x00FF00);
			string tempString = stringWithinWidth( s_song->getName(), songH );
			ofRectangle rect = franklinBook.getStringBoundingBox(tempString, 0,0);
			float centerx = songH / 2; // rect.x + rect.width / 2;
			float centery = rect.y + rect.height / 2;
			ofPushMatrix();
				// Translate and rotate
				ofTranslate(songX + (rect.height / 2),songY + (songH / 2),0);
				ofRotate(270, 0,0,1);
				// Border
				ofNoFill();
				ofSetLineWidth(2);
				ofSetColor(color);
				ofRect(rect.x - centerx, rect.y - centery, songH - 2, rect.height + 4);
				ofFill();
				// Background
				ofSetColor(background_color);
				ofRect(rect.x - centerx, rect.y - centery, songH - 2, rect.height + 4);
				// Name
				ofSetColor(color);
				franklinBook.drawString(tempString, -centerx,-centery);
			ofPopMatrix();
			
			// DrawClips()
			vector<liveSequenceClip*> clip_buffer = s_song->getClips();
			for(int c = 0; c < clip_buffer.size(); c++) { // find number of clips in track
				
				liveSequenceClip* s_clip = clip_buffer[c];
				clipX = trackX + songW;
				clipY = trackY + ((s_clip->getStart() + s_song->getStart()) * beatHeight) - (beat * beatHeight) - (step * beatHeight / 32) + clipP;
				clipH = (s_clip->getLength() * beatHeight) - clipP;
				
				// Color
				if (select_mode == "clip" and s_clip == sequence->getSelectedClip() ) {
					color = orange;
				} else {
					color = grey;
				}
				
				// Border
				ofNoFill();
				ofSetLineWidth(2);
				ofSetColor(color);
				ofRect(clipX, clipY, clipW, clipH);
				ofFill();
				
				// Background
				ofSetColor(background_color);
				ofRect(clipX, clipY, clipW, clipH);
				
				// Name
				ofSetColor(color);
				franklinBook.drawString(s_clip->getName(), clipX, clipY + 15);
				
				// Fire clip if ready:
				if ((s_clip->getStart() == beat + 1) and (step == 0)) {
					cout << "FIRE!!" << endl;
					if (sequencer->getClipMode() == "live") {
						s_clip->getLiveClip()->callFunction("fire");
					}
				}
			}
			
			
			
		}
		
	}
}


// crop string to fit song length by testing against stringWidth
string liveSequenceWindow::stringWithinWidth(string input, int length) {
	ofRectangle rect = franklinBook.getStringBoundingBox(input, 0,0);
	int i = 0;
	while (rect.width > length) {
		input = input.substr(0, 100 - i);
		rect = franklinBook.getStringBoundingBox(input, 0,0);
		// cout << "!! STRING: " << tempString << " WIDTH: " << rect.width << endl;
		i ++;
	}
	return input;
}


void liveSequenceWindow::keyPressed(int key) {
	int selected_song_start = sequence->getSelectedSong()->getStart();
	switch (key) {
		case 'j':
			if (select_mode == "clip") {
				cout << "goin down" << endl;
			} else {
				sequence->getSelectedSong()->setStart(selected_song_start + 4);
			}
			break;
		case 'k':
			if (select_mode == "clip") {
				cout << "goin up" << endl;
			} else {
				sequence->getSelectedSong()->setStart(selected_song_start - 4);
			}
			break;
		case 'l':
			cout << "goin left" << endl;
			break;
		case ';':
			cout << "goin right" << endl;
			break;
		case 'f':
			cout << "toggle" << endl;
			toggleSelectMode();
			break;
		default:
			break;
	}
}


void liveSequenceWindow::toggleSelectMode() {
	if (select_mode == "clip") {
		select_mode = "song";
	} else {
		select_mode = "clip";
	}
}