// Contains logic to render and manipulate sequence

#include "liveSequenceWindow.h"

liveSequenceWindow::liveSequenceWindow(sequencerApp* _sequencer, int _x, int _y, int _w, int _h) {
	sequencer = _sequencer;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	sequence = new liveSequence(sequencer, 1);
	
	selected_song = sequence->getSongs()[0];
	selected_clip = selected_song->getClip(0);
	
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
			if (select_mode == "song" and s_song == selected_song ) {
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
				if (select_mode == "clip" and s_clip == selected_clip ) {
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
				franklinBook.drawString(s_clip->getName() + " s: " + ofToString(s_clip->getStart()), clipX, clipY + 15);
				
				// Fire clip if ready:
				if ((s_clip->getStart() == beat + 1) and (step == 0)) {
					//cout << "FIRE!!" << endl;
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
		i ++;
	}
	return input;
}


void liveSequenceWindow::keyPressed(int key) {
//	cout << "!!KEY: " << key << endl;
	int selected_song_start = selected_song->getStart();
	int selected_track = selected_clip->getSong()->getTrackId();
	switch (key) {
		case 'j':
			cout << "DOWN" << endl;
			if (select_mode == "clip") {
				int selected_order = sequence->getClipOrder(selected_clip);
				int clips_in_selected_track = sequence->getTrackClips(selected_track).size();
				if ( (selected_order + 1) < clips_in_selected_track ) {
					selected_clip = sequence->getTrackClips(selected_track)[selected_order + 1];
				}
			} else {
				selected_song->setStart(selected_song_start + 4);
			}
			break;
		case 'k':
			cout << "UP" << endl;
			if (select_mode == "clip") {
				int selected_order = sequence->getClipOrder(selected_clip);
				if ( (selected_order - 1) >= 0 ) {
					selected_clip = sequence->getTrackClips(selected_track)[selected_order - 1];
				}
			} else {
				selected_song->setStart(selected_song_start - 4);
			}
			break;
		case 'l':
			cout << "LEFT" << endl;
			if (selected_track == 1) {
				selected_clip = sequence->getTrackClips(selected_track - 1)[0];
				selected_song = selected_clip->getSong();
			}
			break;
		case ';':
			cout << "RIGHT" << endl;
			if (selected_track == 0) {
				selected_clip = sequence->getTrackClips(selected_track + 1)[0];
				selected_song = selected_clip->getSong();
			}
			break;
		case 'f':
			cout << "TOGGLE" << endl;
			toggleSelectMode();
			break;
		case 127: // Delete
			cout << "DELETE " << selected_clip->getName() << endl;
			if (select_mode == "clip") {
				selected_clip = selected_song->removeClip(selected_clip);
			}
			break;
		case 13:  // Enter
			cout << "DUPLICATE " << selected_clip->getName() << endl;
			if (select_mode == "clip") {
				selected_clip = selected_song->duplicateClip(selected_clip);
			}
			break;
		default:
			break;
	}
}


void liveSequenceWindow::toggleSelectMode() {
	if (select_mode == "clip") {
		select_mode = "song";
		selected_song = selected_clip->getSong();
	} else {
		select_mode = "clip";
		selected_clip = selected_song->getClips()[0];
	}
}