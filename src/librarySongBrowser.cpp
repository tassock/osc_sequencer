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
	
	view = "song_select";
	
	loadSongBuffer();
	updateQueryBuffer();
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


void librarySongBrowser::updateQueryBuffer() {
	
	// lowercase query
	string lwr_query = query;
	std::transform(lwr_query.begin(), lwr_query.end(), lwr_query.begin(), ::tolower);
	
	// empty buffer
	query_buffer.clear();
	
	// filter songs
	for(int i = 0; i < song_buffer.size(); i++) {
		librarySong* s_song = song_buffer[i];
		size_t found = s_song->getLowercaseName().find(lwr_query);
		if ( lwr_query == "" or (found!=string::npos) ) {
			query_buffer.insert ( query_buffer.end(), s_song);
		}
	}
}


void librarySongBrowser::draw() {
	
	int padding = 20;
	
	if (view == "song_select") {
		// Search box
		ofSetColor(255, 255, 255);
		ofRect(browserX + padding, browserY + padding, browserW - (2 * padding), 30);
		ofSetColor(0, 0, 0);
		string query_text = query;
		query_text =query + "|";
		franklinBook.drawString( query_text, browserX + padding, browserY + (2 * padding) );
		
		// Song list
		for(int i = 0; i < query_buffer.size(); i++) {
			librarySong* s_song = query_buffer[i];
			if (i == select_index) {
				ofSetColor(ORANGE);
			} else {
				ofSetColor(255, 255, 255);
			}
			franklinBook.drawString( s_song->getName(), browserX + padding, browserY + 70 + (i * 20) );
		}
	} else {
		ofSetColor(255, 255, 255);
		franklinBook.drawString( "sequences", browserX + padding, browserY + padding );
		
		librarySong* s_song = query_buffer[select_index];
		vector<clip*> s_clips = s_song->getClips();
		int shift = 0;
		for(int i = 0; i < s_clips.size(); i++) {
			clip* s_clip = s_clips[i];
			s_clip->draw(browserX + padding, browserY + (2 * padding) + (shift * BEAT_HEIGHT ), false, true );
			shift = shift + s_clip->getLength();
		}
	}
}


void librarySongBrowser::keyPressed(int key) {
	if (view == "sequence_select") {
		switch (key) {
//			case 13: // Enter
//				cout << "INSERT: " << query_buffer[select_index]->getName() << endl;
//				break;
			case 9: // Tab
				break;
			case 92: // |
				cout << "EXIT" << endl;
				view = "song_select";
				break;
		}
	} else {
		switch (key) {
			case 92: // /
				break;
			case 13: // Enter
				cout << "ENTER" << endl;
				view = "sequence_select";
				cout << "SIZE: " << query_buffer[select_index]->getSequenceSongs().size() << endl;
				break;
			case 127: // Delete
				cout << "DELETE" << endl;
				query = query.substr(0, query.size()-1);
				updateQueryBuffer();
				break;
			case 9: // Tab
				cout << "Change selection" << endl;
				if (select_index < (query_buffer.size() - 1) ) {
					select_index ++;
				} else {
					select_index = 0;
				}
				break;
			default:
				cout << "!!BROSWER KEY: " << key << endl;
				char buf = key;
				query = query + buf;
				updateQueryBuffer();
			break;
		}
	}
}


string librarySongBrowser::getView() {
	return view;
}


librarySong* librarySongBrowser::getSelectedSong() {
	view = "song_select";
	return query_buffer[select_index];
}