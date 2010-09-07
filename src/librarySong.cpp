#include "librarySong.h"

// Old Constructor
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
	
	loadClips();
}

// New Constructor
librarySong::librarySong(sequencerApp* _sequencer, int _id, string _artist, string _title, int _bpm, int _key, int _major) {
	sequencer = _sequencer;
	id = _id;
	artist = _artist;
	title = _title;
	bpm = _bpm;
	key = _key;
	major = _major;
	
	loadClips();
}


void librarySong::loadClips() {
	// Get clips
	ofxSQLiteSelect sel = sequencer->getSQLite()->select("id, length, live_id")
	.from("library_clips")
	.where("song_id", id)
	.execute().begin();
	while(sel.hasNext()) {
		int _id = sel.getInt();
		int _length = sel.getInt();
		string _live_id = sel.getString();
		clips.insert ( clips.end(), new clip(sequencer, _id, _length, _live_id) );
		sel.next();
	}
}


string librarySong::getName() {
	return (artist + " - " + title);
}


string librarySong::getLowercaseName() {
	string data = getName();
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}


vector<clip*> librarySong::getClips() {
	return clips;
}


clip* librarySong::getClip(int index) {
	return clips[index];
}