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
		songs.insert ( songs.begin(), new liveSequenceSong(sequencer, sequence_song_id, song_id, track_id, bar_start, length) );
		
		selected_song = songs[0];
		
		// next record
		sel.next();
	}
}


//int liveSequence::numSongsInTrack(int track_id) {
//	int count = 0;
//	for(int i = 0; i < num_songs; i++) {
//		liveSequenceSong* s_song = songs[i];
//		if (s_song->getTrackId() == track_id) {
//			count += 1;
//		}
//	}
//	return count;
//}
//
//
//liveSequenceSong* liveSequence::getSongInTrack(int track_id, int song_order) {
//	int offset = 0;
//	for(int i = 0; i < num_songs; i++) {
//		liveSequenceSong* s_song = songs[i];
//		if (s_song->getTrackId() == track_id) {
//			if (offset == song_order) {
//				return songs[i];
//			} else {
//				offset += 1;
//			}
//		}
//	}
//}


vector<liveSequenceSong*> liveSequence::getTrackSongs(int track_id) {
	vector<liveSequenceSong*> song_buffer;
	for(int i = 0; i < songs.size(); i++) {
		liveSequenceSong* s_song = songs[i];
		if (s_song->getTrackId() == track_id) {
			song_buffer.insert(song_buffer.begin(), s_song);
		}
	}
	return song_buffer;
}


vector<liveSequenceClip*> liveSequence::getTrackClips(int track_id) {
	vector<liveSequenceSong*> song_buffer = getTrackSongs(track_id);
	vector<liveSequenceClip*> clip_buffer;
	for(int i = 0; i < song_buffer.size(); i++) {
		liveSequenceSong* s_song = song_buffer[i];
		vector<liveSequenceClip*> song_clip_buffer = s_song->getClips();
		for(int c = 0; c < song_clip_buffer.size(); c++) {
			liveSequenceClip* clip_insert = song_clip_buffer[c];
			clip_buffer.insert( clip_buffer.begin(), clip_insert );
		}
	}
	return clip_buffer;
}


string liveSequence::getName() {
	return name;
}


liveSequenceSong* liveSequence::getSelectedSong() {
	return selected_song;
}


liveSequenceClip* liveSequence::getSelectedClip() {
	return selected_song->getClip(0);
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