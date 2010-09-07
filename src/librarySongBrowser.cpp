/*
 *  librarySongBrowser.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/6/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "librarySongBrowser.h"

librarySongBrowser::librarySongBrowser(sequencerApp* _sequencer) {
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	
	select_index = 0;
	
	browserX = 45;
	browserY = 300;
	browserH = 520;
	browserW = 420;
	
	franklinBook.loadFont("frabk.ttf", 12);
	
	loadSongBuffer();
}


// load librarySong objects into song_buffer
void librarySongBrowser::loadSongBuffer() {
	cout << "loadSongBuffer" << endl;
	// select all that match sequence id
	ofxSQLiteSelect sel = sqlite->select("id, artist, title, bpm, key, major")
	.from("library_songs")
	.execute().begin();
	
	// set results as instance variables
	while(sel.hasNext()) {
		cout << "NEXT" << endl;
		int _id = sel.getInt();
		string _artist = sel.getString();
		string _title = sel.getString();
		int _bpm = sel.getInt();
		int _key = sel.getInt();
		int _major = sel.getInt();
		
		// store sequence clip in buffer
		song_buffer.insert ( song_buffer.end(), new librarySong(sequencer, _id, _artist, _title, _bpm, _key, _major) );
		
		// next record
		sel.next();
	}
}

void librarySongBrowser::draw() {
	
	int padding = 20;
	
	// Search box
	ofSetColor(255, 255, 255);
	ofRect(browserX + padding, browserY + padding, browserW - (2 * padding), 30);
	ofSetColor(0, 0, 0);
	string query_text = query;
	query_text =query + "|";
	franklinBook.drawString( query_text, browserX + padding, browserY + (2 * padding) );
	
	// lowercase query
	string lwr_query = query;
	std::transform(lwr_query.begin(), lwr_query.end(), lwr_query.begin(), ::tolower);
	
	// Song list
	int count = 0;
	for(int i = 0; i < song_buffer.size(); i++) {
		// filter songs
		librarySong* s_song = song_buffer[i];
		size_t found = s_song->getLowercaseName().find(lwr_query);
		if ( lwr_query == "" or (found!=string::npos) ) {
			// draw selector
			if (count == select_index) {
				ofSetColor(255, 255, 0);
			} else {
				ofSetColor(255, 255, 255);
			}
			franklinBook.drawString( s_song->getName(), browserX + padding, browserY + 70 + (count * 20) );
			count ++;
		}
	}
}


void librarySongBrowser::keyPressed(int key) {
	switch (key) {
		case 92: // /
			break;
		case 13: // Enter
			cout << "ENTER" << endl;
			break;
		case 127: // Delete
			cout << "DELETE" << endl;
			query = query.substr(0, query.size()-1);
			break;
		case 9: // Tab
			cout << "Change selection" << endl;
			select_index ++;
			break;
		default:
			cout << "!!BROSWER KEY: " << key << endl;
			char buf = key;
			query = query + buf;
			break;
	}
}