#include "liveSequenceSong.h"

liveSequenceSong::liveSequenceSong(sequencerApp* _sequencer, int _id, int _song_id, int _track_id, int _bar_start, int _length) {
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	id = _id;
	song_id = _song_id;
	track_id = _track_id;
	bar_start = _bar_start;
	length = _length;
	
	// Get library song
	library_song = new librarySong(sequencer, song_id);
	name = library_song->getName();
	
	// Load clips
	loadClips();
}


void liveSequenceSong::loadClips() {
	// select all that match sequence id
	ofxSQLiteSelect sel = sqlite->select("id, clip_id, track_id, bar_start, length")
	.from("sequence_clips")
	.where("sequence_song_id", id)
	.execute().begin();
	
	// set results as instance variables
	while(sel.hasNext()) {
		int sequence_clip_id = sel.getInt();
		int clip_id = sel.getInt();
		int track_id = sel.getInt();
		int bar_start = sel.getInt();
		int length = sel.getInt();
		
		// store sequence clip in buffer
		clips.insert ( clips.begin(), new liveSequenceClip(sequencer, sequence_clip_id, clip_id, track_id, bar_start, length) );
		
		// next record
		sel.next();
	}
}


liveSequenceClip* liveSequenceSong::getClip(int index) {
	return clips[index];
}


vector<liveSequenceClip*> liveSequenceSong::getClips() {
	return clips;
}


int liveSequenceSong::getNumClips() {
	return num_clips;
}


int liveSequenceSong::getTrackId() {
	return track_id;
}


string liveSequenceSong::getName() {
	return name;
}


int liveSequenceSong::getStart() {
	return bar_start;
}

void liveSequenceSong::setStart(int bar) {
	bar_start = bar;
}


int liveSequenceSong::getEnd() {
	return bar_start + length;
}


int liveSequenceSong::getLength() {
	return length;
}