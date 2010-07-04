#include "liveSequence.h"

liveSequence::liveSequence(ofxSQLite* _sqlite, int _id) {
	id = _id;
	sqlite = _sqlite;
	
	// Get name from database
	ofxSQLiteSelect sel = sqlite->select("name")
	.from("sequences")
	.where("id", 1)
	.execute().begin();
	while(sel.hasNext()) {
		name = sel.getString();
		sel.next();
	}
	
	loadClips();
}


void liveSequence::loadClips() {
	// select all that match sequence id
	ofxSQLiteSelect sel = sqlite->select("id, clip_id, track_id, bar_start, length")
	.from("sequence_clips")
	.where("sequence_id", id)
	.execute().begin();
	
	// set results as instance variables
	int count = 0;
	while(sel.hasNext()) {
		int sequencer_clip_id = sel.getInt();
		int clip_id = sel.getInt();
		int track_id = sel.getInt();
		int bar_start = sel.getInt();
		int length = sel.getInt();
		
		// store sequence clip in buffer
		clips[count] = new liveSequenceClip(sqlite, sequencer_clip_id, clip_id, track_id, bar_start, length);
		
		// next record
		count ++;
		sel.next();
	}
	
	// set clip count
	num_clips = count;
}


int liveSequence::numClipsInTrack(int track_id) {
	int count = 0;
	for(int i = 0; i < num_clips; i++) {
		liveSequenceClip* s_clip = clips[i];
		if (s_clip->getTrackId() == track_id) {
			count += 1;
		}
	}
	return count;
}


liveSequenceClip* liveSequence::getClipInTrack(int track_id, int clip_order) {
	int offset = 0;
	for(int i = 0; i < num_clips; i++) {
		liveSequenceClip* s_clip = clips[i];
		if (s_clip->getTrackId() == track_id) {
			if (offset == clip_order) {
				return clips[i];
			} else {
				offset += 1;
			}
		}
	}
}


string liveSequence::getName() {
	return name;
}