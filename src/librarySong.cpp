#include "librarySong.h"

librarySong::librarySong(sequencerApp* _sequencer, int _id) {
	sequencer = _sequencer;
	id = _id;
	
	// Get attributes from database
	ofxSQLiteSelect sel = sequencer->getSQLite()->select("artist, title, bpm, key, major")
	.from("library_songs")
	.where("id", id)
	.execute().begin();
	while(sel.hasNext()) {
		artist = sel.getString();
		title = sel.getString();
		bpm = sel.getInt();
		key = sel.getInt();
		major = sel.getInt();
		sel.next();
	}
}

string librarySong::getName() {
	return (artist + " - " + title);
}