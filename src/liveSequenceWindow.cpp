// Contains logic to render and manipulate sequence

#include "liveSequenceWindow.h"

liveSequenceWindow::liveSequenceWindow(sequencerApp* _sequencer, int _x, int _y, int _w, int _h) {
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	sequence = new liveSequence(sequencer, 1);
	
	selected_song = sequence->getSongs()[0];
	selected_clip = selected_song->getClip(0);
	
	select_mode = "song";
	
	franklinBook.loadFont("frabk.ttf", 12);
	loadSongBuffer();
}

void liveSequenceWindow::draw(int beat, int step) {
	
	drawBrowser();
	
	// Background
	ofRect(x, y, w, h);
	
	// Sequencer vars
	int beatHeight = 20;
	int padding = 5;
	
	// Track vars
	int trackX = 0;
	int trackY = y + 20;
	int trackW = 180;
	int trackH = 750;
	
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


void liveSequenceWindow::drawBrowser() {
	int x = 640;
	int y = 300;
	int w = 420;
	int h = 520;
	
	// Background
	ofSetColor(50, 50, 50);
	ofRect(x, y, w, h);
	
	// Search box
	ofSetColor(255, 255, 255);
	ofRect(x + 20, y + 20, w - 40, 30);
	
	// Song list
	for(int i = 0; i < song_buffer.size(); i++) {
		librarySong* s_song = song_buffer[i];
		franklinBook.drawString( s_song->getName(), x + 20, y + 70 + (i * 20) );
	}
}


// load librarySong objects into song_buffer
void liveSequenceWindow::loadSongBuffer() {
	// select all that match sequence id
	ofxSQLiteSelect sel = sqlite->select("id")
	.from("library_songs")
	.execute().begin();
	
	// set results as instance variables
	while(sel.hasNext()) {
		int song_id = sel.getInt();
		
		// store sequence clip in buffer
		song_buffer.insert ( song_buffer.end(), new librarySong(sequencer, song_id) );
		
		// next record
		sel.next();
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
	cout << "!!KEY: " << key << endl;
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
				// check if there's room
				int next_song_start = sequence->nextSongStart( selected_song->getTrackId(), selected_song->getEnd() );
				if ( next_song_start >= (selected_song->getEnd() + 4) ) {
					selected_song->setStart(selected_song_start + 4);
				}
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
				// check if there's room
				int prev_song_end = sequence->prevSongEnd( selected_song->getTrackId(), selected_song->getStart() );
				if ( prev_song_end <= (selected_song->getStart() - 4) ) {
					selected_song->setStart(selected_song_start - 4);
				}
			}
			break;
		case 'l':
			cout << "LEFT" << endl;
			if (select_mode == "clip") {
				// change selected_clip
				if (selected_track == 1) {
					selected_clip = sequence->getTrackClips(selected_track - 1)[0];
					selected_song = selected_clip->getSong();
				}
			} else {
				// move selected song left
				if (selected_track == 1) {
					// check if there's room in the other track
					int next_song_start = sequence->nextSongStart(0, selected_song->getStart() );
					int prev_song_end = sequence->prevSongEnd(0, selected_song->getEnd() );
					cout << "prev_song_end: " << prev_song_end << endl;
					if ( next_song_start >= (selected_song->getEnd()) and prev_song_end <= (selected_song->getStart()) ) {
						selected_song->setTrackId(0);
					}
				}
			}
			break;
		case ';':
			cout << "RIGHT" << endl;
			if (select_mode == "clip") {
				// change selected_clip
				if (selected_track == 0) {
					selected_clip = sequence->getTrackClips(selected_track + 1)[0];
					selected_song = selected_clip->getSong();
				}
			} else {
				// move selected song left
				if (selected_track == 0) {
					// check if there's room in the other track
					int next_song_start = sequence->nextSongStart(1, selected_song->getStart() );
					int prev_song_end = sequence->prevSongEnd(1, selected_song->getEnd() );
					if ( next_song_start >= (selected_song->getEnd()) and prev_song_end <= (selected_song->getStart()) ) {
						selected_song->setTrackId(1);
					}
				}
			}
			
			
			break;
		case 'f':
			cout << "TOGGLE" << endl;
			toggleSelectMode();
			break;
		case 's':
			cout << "SAVE" << endl;
			sequence->save();
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
				// check if there's room
				int next_song_start = sequence->nextSongStart( selected_song->getTrackId(), selected_song->getEnd() );
				if ( next_song_start >= (selected_song->getEnd() + selected_clip->getLength() ) ) {
					selected_clip = selected_song->duplicateClip(selected_clip);
				}
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