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


void liveSequenceSong::save() {
	cout << "SAVING SONG" << endl;
	
	// Update self
	sqlite->update("sequence_songs")
	.use("bar_start", bar_start)
	.where("id", id)
	.execute();
	
	// Update clips
	for(int i = 0; i < clips.size(); i++) {
		clips[i]->save();
	}
}


// load liveSequenceClip objects into buffer
void liveSequenceSong::loadClips() {
	// select all that match sequence id
	ofxSQLiteSelect sel = sqlite->select("id, clip_id, track_id, bar_start, length")
	.from("sequence_clips")
	.where("sequence_song_id", id)
	.order("bar_start", " ASC ")
	.execute().begin();
	
	// set results as instance variables
	while(sel.hasNext()) {
		int sequence_clip_id = sel.getInt();
		int clip_id = sel.getInt();
		int track_id = sel.getInt();
		int bar_start = sel.getInt();
		int length = sel.getInt();
		
		// store sequence clip in buffer
		clips.insert ( clips.end(), new liveSequenceClip(sequencer, this, sequence_clip_id, clip_id, track_id, bar_start, length) );
		
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


// Remove given clip from buffer. Return next clip in buffer. 
liveSequenceClip* liveSequenceSong::removeClip(liveSequenceClip* delete_clip) {
	if (clips.size() == 1) {
		return delete_clip;
	} else {
		// remove delete clip, shift succeeding clips up.
		int next_clip_index = 0;
		bool deleted = false;
		int clip_count = clips.size();
		for(int c = 0; c < clips.size(); c++) {
			if (clips[c] == delete_clip) {
				cout << "DELETE " << clips[c]->getName() << endl;
				clips.erase( clips.begin() + c );
				next_clip_index = c;
				deleted = true;
			}
			if (deleted) {
				int new_start = clips[c]->getStart() - delete_clip->getLength();
				cout << "SHIFT: " << clips[c]->getName() << ", s: " << new_start << endl;
				// Shift clip up
				clips[c]->setStart( new_start );
			}
		}
		// Check if next_clip_index is out of bounds 
		cout << "SIZE " << clips.size() << endl;
		cout << "next_clip_index " << next_clip_index << endl;
		if ( next_clip_index >= (clips.size() - 1) ) {
			next_clip_index = clips.size() - 1;
		}
		cout << "next_clip_index " << next_clip_index << endl;
		// Return next clip
		return clips[next_clip_index];
	}
}


// Duplicate given clip. Return duplicated clip. 
liveSequenceClip* liveSequenceSong::duplicateClip(liveSequenceClip* duplicate_clip) {
	int new_clip_index = 0;
	bool duplicated = false;
	for(int c = 0; c < clips.size(); c++) {
		if (clips[c] == duplicate_clip) {
			cout << "DUPLICATE " << clips[c]->getName() << endl;
			clips.insert( clips.begin() + c, new liveSequenceClip(sequencer, duplicate_clip) );
			new_clip_index = c;
			duplicated = true;
			c++;
		}  
		if (duplicated) {
			int new_start = clips[c]->getStart() + duplicate_clip->getLength();
			cout << "SHIFT: " << clips[c]->getName() << ", s: " << new_start << endl;
			// Shift clip down
			clips[c]->setStart( new_start );
		}
	}
	// Return new clip
	cout << "NEW SIZE: " << clips.size() << endl;
	return clips[new_clip_index];
}


int liveSequenceSong::getNumClips() {
	return num_clips;
}


int liveSequenceSong::getId() {
	return id;
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
	//return length;
	int start = clips[0]->getStart();
	int end = clips[clips.size() - 1]->getEnd();
	return end - start;
}