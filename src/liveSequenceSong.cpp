#include "liveSequenceSong.h"

liveSequenceSong::liveSequenceSong(sequencerApp* _sequencer, int _id, int _song_id, int _track_id, int _bar_start, int _length) {
	sequencer = _sequencer;
	id = _id;
	song_id = _song_id;
	track_id = _track_id;
	bar_start = _bar_start;
	length = _length;
	
	// Get library song
	library_song = new librarySong(sequencer, song_id);
	name = library_song->getName();
}

int liveSequenceSong::getTrackId() {
	return track_id;
}


int liveSequenceSong::getStart() {
	return bar_start;
}


int liveSequenceSong::getEnd() {
	return bar_start + length;
}


int liveSequenceSong::getLength() {
	return length;
}