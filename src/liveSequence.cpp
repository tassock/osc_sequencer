#include "liveSequence.h"

liveSequence::liveSequence(sequencerApp* _sequencer, int _id) {
	id = _id;
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	select_mode = "clip";
	
	// Get name from database
	ofxSQLiteSelect sel = sqlite->select("name")
	.from("sequences")
	.where("id", 1)
	.execute().begin();
	while(sel.hasNext()) {
		name = sel.getString();
		sel.next();
	}
	
	loadSongs();
}

//--------------------------------------------------------------
// Query for liveSequencerSong's in the sequence. Load the song and its clips into buffers. 
void liveSequence::loadSongs() {
	
	// select all that match sequence id
	ofxSQLiteSelect sel = sqlite->select("id, song_id, track_id, bar_start, length")
	.from("sequence_songs")
	.where("sequence_id", id)
	.execute().begin();
	
	// set results as instance variables
	while(sel.hasNext()) {
		int sequence_song_id = sel.getInt();
		int song_id = sel.getInt();
		int track_id = sel.getInt();
		int bar_start = sel.getInt();
		int length = sel.getInt();
		
		// store sequence song in buffer
		songs.insert ( songs.end(), new liveSequenceSong(sequencer, sequence_song_id, song_id, track_id, bar_start, length) );
		
		// next record
		sel.next();
	}
}


vector<liveSequenceSong*> liveSequence::getSongs() {
	return songs;
}


vector<liveSequenceSong*> liveSequence::getTrackSongs(int track_id) {
	vector<liveSequenceSong*> song_buffer;
	for(int i = 0; i < songs.size(); i++) {
		liveSequenceSong* s_song = songs[i];
		if (s_song->getTrackId() == track_id) {
			song_buffer.insert(song_buffer.end(), s_song);
		}
	}
	
	// log contents
//	for(int i = 0; i < song_buffer.size(); i++) {
//		cout << "TRACK#" << track_id << " getTrackSongs: #" << i << ", " << song_buffer[i]->getName() << endl;
//	}
	
	return song_buffer;
}	


vector<liveSequenceClip*> liveSequence::getTrackClips(int track_id) {
	vector<liveSequenceSong*> song_buffer = getTrackSongs(track_id);
	vector<liveSequenceClip*> clip_buffer;
	for(int i = 0; i < song_buffer.size(); i++) {
		liveSequenceSong* s_song = song_buffer[i];
//		cout << "TRACK#" << track_id << " getTrackClips: #" << i << ", " << s_song->getName() << endl;
		vector<liveSequenceClip*> song_clip_buffer = s_song->getClips();
		for(int c = 0; c < song_clip_buffer.size(); c++) {
			liveSequenceClip* clip_insert = song_clip_buffer[c];
			clip_buffer.insert( clip_buffer.end(), clip_insert );
		}
	}
	
//	// log contents
//	for(int i = 0; i < clip_buffer.size(); i++) {
//		cout << "getTrackClips: #" << i << ", " << clip_buffer[i]->getName() << endl;
//	}
	
	return clip_buffer;
}


int liveSequence::getClipOrder(liveSequenceClip* l_clip) {
	int track_id = l_clip->getSong()->getTrackId();
	vector<liveSequenceClip*> clip_buffer = getTrackClips(track_id);
	for(int i = 0; i < clip_buffer.size(); i++) {
		if (clip_buffer[i] == l_clip) {
			return i;
		}
	}
}


string liveSequence::getName() {
	return name;
}


void liveSequence::selectPosition(char direction) {
//	switch (direction) {
//		case 'j':
//			if (select_mode == "clip") {
//				cout << "goin down" << endl;
//			} else {
//				selected_song->setStart(start + 4);
//			}
//			break;
//		case 'k':
//			if (select_mode == "clip") {
//				cout << "goin up" << endl;
//			} else {
//				selected_song->setStart(start - 4);
//			}
//			break;
//		case 'l':
//			cout << "goin left" << endl;
//			break;
//		case 'r':
//			cout << "goin right" << endl;
//			break;
//		default:
//			break;
//	}

}