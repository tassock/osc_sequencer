#include "liveSequence.h"

liveSequence::liveSequence(sequencerApp* _sequencer, int _id) {
	id = _id;
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	
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
	int count = 0;
	while(sel.hasNext()) {
		int sequence_song_id = sel.getInt();
		int song_id = sel.getInt();
		int track_id = sel.getInt();
		int bar_start = sel.getInt();
		int length = sel.getInt();
		
		// store sequence song in buffer
		songs[count] = new liveSequenceSong(sequencer, sequence_song_id, song_id, track_id, bar_start, length);
		
		// next record
		count ++;
		sel.next();
	}
	
	// set clip count
	num_songs = count;
}


int liveSequence::numSongsInTrack(int track_id) {
	int count = 0;
	for(int i = 0; i < num_songs; i++) {
		liveSequenceSong* s_song = songs[i];
		if (s_song->getTrackId() == track_id) {
			count += 1;
		}
	}
	return count;
}


liveSequenceSong* liveSequence::getSongInTrack(int track_id, int song_order) {
	int offset = 0;
	for(int i = 0; i < num_songs; i++) {
		liveSequenceSong* s_song = songs[i];
		if (s_song->getTrackId() == track_id) {
			if (offset == song_order) {
				return songs[i];
			} else {
				offset += 1;
			}
		}
	}
}


string liveSequence::getName() {
	return name;
}


liveSequenceSong* liveSequence::getSelectedSong() {
	return songs[0];
}