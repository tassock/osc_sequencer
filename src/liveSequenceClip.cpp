#include "liveSequenceClip.h"

// Constructor to load existing liveSequenceClip from db
liveSequenceClip::liveSequenceClip(sequencerApp* _sequencer, liveSequenceSong* _song, int _id, int _clip_id, int _track_id, int _sequence_song_order, int _length) {
	sequencer = _sequencer;
	song = _song;
	sqlite = sequencer->getSQLite();
	
	id = _id;
	clip_id = _clip_id;
	track_id = _track_id;
	sequence_song_order = _sequence_song_order;
	length = _length;
	
	// Get library clip
	library_clip = new clip(clip_id, sqlite);
	name = library_clip->getName();
	
	fetchLiveClip();
	
	cout << "CLIP: id:" << id << ", name:" << name << ", clip_id:" << clip_id << ", sequence_song_order:" << sequence_song_order << ", length:" << length << endl;
}


// Constructor for duplicate liveSequenceClip
liveSequenceClip::liveSequenceClip(sequencerApp* _sequencer, liveSequenceClip* duplicate_clip) {
	sequencer = _sequencer;
	song = duplicate_clip->getSong();
	sqlite = sequencer->getSQLite();
	
	id = NULL;
	clip_id   = duplicate_clip->getClipId();
	track_id  = duplicate_clip->getTrackId();
	sequence_song_order = duplicate_clip->getOrder();
	length    = duplicate_clip->getLength();
	
	library_clip = duplicate_clip->getClip();
	name = library_clip->getName();
	
	fetchLiveClip();
}


// Constructor for new liveSequenceClip
liveSequenceClip::liveSequenceClip(sequencerApp* _sequencer, liveSequenceSong* _song, clip* _clip, int _sequence_song_order) {
	sequencer = _sequencer;
	song = _song;
	sqlite = sequencer->getSQLite();
	
	id = NULL;
	clip_id = _clip->getId();
	track_id = _song->getTrackId();
	sequence_song_order = _sequence_song_order;
	length = _clip->getLength();
	
	library_clip = _clip;
	name = library_clip->getName();
	
	fetchLiveClip();
}
	


void liveSequenceClip::save() {
	cout << "SAVING CLIP" << endl;
	
	if (id == NULL) {
		// Save self
		sqlite->insert("sequence_clips")
		.use("clip_id", clip_id)
		.use("track_id", track_id)
		.use("sequence_song_order", sequence_song_order)
		.use("length", length)
		.use("sequence_song_id", song->getId())
		.execute();
		// Set id
		id = sqlite->lastInsertID();
	} else {
		// Update self
		sqlite->update("sequence_clips")
		.use("sequence_song_order", sequence_song_order)
		.where("id", id)
		.execute();
	}
}


void liveSequenceClip::fetchLiveClip() {
	if (sequencer->getClipMode() == "live") {
		live_clip = sequencer->getCurrentSet()->getClipByName(name, song->getTrackId());
	}
}


liveClip* liveSequenceClip::getLiveClip() {
	return live_clip;
}


liveSequenceSong* liveSequenceClip::getSong() {
	return song;
}


int liveSequenceClip::getId() {
	return id;
}


int liveSequenceClip::getClipId() {
	return clip_id;
}


clip* liveSequenceClip::getClip() {
	return library_clip;
}


int liveSequenceClip::getTrackId() {
	return track_id;
}


string liveSequenceClip::getName() {
	return name;
}


int liveSequenceClip::getOrder() {
	return sequence_song_order;
}


void liveSequenceClip::setOrder(int _order) {
	sequence_song_order = _order;
}


int liveSequenceClip::getLength() {
	return length;
}