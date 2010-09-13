// Contains logic to render and manipulate sequence

#include "liveSequenceWindow.h"

liveSequenceWindow::liveSequenceWindow(sequencerApp* _sequencer, int _x, int _y, int _w, int _h) {
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	browserX = 45;
	browserY = 300;
	browserH = 520;
	browserW = 420;
	
	song_browser = new librarySongBrowser(sequencer);
	
	clip_select_index = 0;
	sequence = new liveSequence(sequencer, 2);
	
	selected_song = sequence->getSongs()[0];
	selected_clip = selected_song->getClip(0);
	clip_buffer = selected_song->getLibrarySong()->getClips();
	
	select_mode = "song";
	focus = "sequence";
	
	franklinBook.loadFont("frabk.ttf", 12);
}


void liveSequenceWindow::update(int beat, int step) {
	fireClips(beat, step);
}


void liveSequenceWindow::draw(int beat, int step) {
	
	// Background
	ofSetColor(0, 0, 0);
	ofRect(x, y, w, h);
	
	// Sequencer vars
	int padding = 5;
	
	// Track vars
	int trackX = 0;
	int trackY = y;
	int trackW = 250;
	int trackH = 1000;
	
	// Draw tracks
	for(int t = 0; t < NUM_S_TRACKS; t++){
		ofSetColor(30, 30, 30);
		trackX = x + padding + (t * (trackW + padding));
		ofRect(trackX, trackY, trackW, trackH);
		// DrawSongs()
		vector<liveSequenceSong*> song_buffer = sequence->getTrackSongs(t);
		for(int c = 0; c < song_buffer.size(); c++) { // find number of songs in track
			liveSequenceSong* s_song = song_buffer[c];
			int songX = trackX;
			int songY = trackY + (s_song->getStart() * BEAT_HEIGHT) - (beat * BEAT_HEIGHT) - (step * BEAT_HEIGHT / 32);
			s_song->draw(songX, songY, select_mode, selected_song, selected_clip);
		}
	}
	drawBrowser();
}


void liveSequenceWindow::drawBrowser() {
	
	if (focus == "browser") {
		
		// Mute sequencer background
		ofSetColor(0, 0, 0, 130);
		ofRect(x, y, w, h);
		
		// Browser background
		ofSetColor(50, 50, 50);
		ofRect(browserX, browserY, browserW, browserH);
		
		if (select_mode == "clip") {
			drawClipBrowser();
		} else if (select_mode == "song") {
			song_browser->draw();
		}
		
	}
}


void liveSequenceWindow::drawClipBrowser() {
	
	int padding = 20;
	
	// song name
	ofSetColor(255, 255, 255);
	franklinBook.drawString( selected_song->getName(), browserX + padding, browserY + padding);
	
	for(int i = 0; i < clip_buffer.size(); i++) {
		clip* s_clip = selected_song->getLibrarySong()->getClip(i);
		bool selected = (clip_select_index == i);
		s_clip->draw(browserX + padding, browserY + (2 * padding) + (i * s_clip->getLength() * BEAT_HEIGHT ), selected );
	}
}


// Handle key press
void liveSequenceWindow::keyPressed(int key) {
	cout << "!!KEY: " << key << endl;
	
	// listen for browser exit
	if (key == 92 and focus == "browser" and song_browser->getView() == "song_select") { // |
		focus = "sequence";
	}
	
	// listen for song insertion
	if (key == 13 and focus == "browser" and song_browser->getView() == "sequence_select") { // ENTER
		librarySong* i_song = song_browser->getSelectedSong();
		cout << "INSERT: " << i_song->getName() << endl;
		selected_song = sequence->addLibrarySong( i_song, selected_song->getTrackId(), selected_song->getEnd() );
		focus = "sequence";
	}
	
	// direct focus specific key actions
	if (focus == "sequence") {
		sequenceKeyPressed(key);
	} else if (focus == "browser") {
		if (select_mode == "clip") {
			clipBrowserKeyPressed(key);
		} else if (select_mode == "song") {
			song_browser->keyPressed(key);
		}
	}
	
	// listen for browser entry
	if (key == 'i' and focus == "sequence") {
		focus = "browser";
	}
	
}


// Handle key press in browser focus
void liveSequenceWindow::clipBrowserKeyPressed(int key) {
	switch (key) {
		case 92: // /
			break;
		case 13: // Enter
			cout << "ENTER" << endl;
			cout << "INSERT CLIP " << clip_buffer[clip_select_index]->getName() << endl;
			selected_song->insertClip( clip_buffer[clip_select_index], sequence->getClipOrder(selected_clip) );
			focus = "sequence";
			break;
		case 'j': // UP
			if (clip_select_index > 0) {
				clip_select_index = clip_select_index - 1;
			}
			break;
		case 'k': // DOWN
			if (clip_select_index < (clip_buffer.size() - 1) ) {
				clip_select_index ++;
			}
			break;
	}
}


// Handle key press in sequence focus
void liveSequenceWindow::sequenceKeyPressed(int key) {
	int selected_song_start = selected_song->getStart();
	int selected_track = selected_clip->getSong()->getTrackId();
	switch (key) {
		case 'k':
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
		case 'j':
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

// Fire clip if ready:
void liveSequenceWindow::fireClips(int beat, int step) {
	vector<liveSequenceSong*> song_buffer = sequence->getSongs();
	for(int c = 0; c < song_buffer.size(); c++) { // find number of songs in track
		liveSequenceSong* s_song = song_buffer[c];
		vector<liveSequenceClip*> s_clip_buffer = s_song->getClips();
		int bar_count = 0;
		for(int c = 0; c < s_clip_buffer.size(); c++) { // find number of clips in track
			
			liveSequenceClip* s_clip = s_clip_buffer[c];
			int bar_start = bar_count + s_song->getStart();
			
			// Fire clip if ready:
			if (step == 0 and bar_start == beat + 1) {
				//cout << "beat: " << beat << ", start: " << s_clip->getRealStart() << endl;
				if (sequencer->getClipMode() == "live") {
					s_clip->fetchLiveClip();
					cout << "FIRE!! " << s_clip->getName() << endl;
					cout << "NAME!! " << s_clip->getLiveClip()->getName() << endl;
					s_clip->getLiveClip()->fire();
				}
			}
			
			bar_count = bar_count + s_clip->getLength();
		}
	}
}
	