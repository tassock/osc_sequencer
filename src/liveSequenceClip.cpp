#include "liveSequenceClip.h"

liveSequenceClip::liveSequenceClip(sequencerApp* _sequencer, liveSequenceSong* _song, int _id, int _clip_id, int _track_id, int _bar_start, int _length) {
	sequencer = _sequencer;
	song = _song;
	sqlite = sequencer->getSQLite();
	
	id = _id;
	clip_id = _clip_id;
	track_id = _track_id;
	bar_start = _bar_start;
	length = _length;
	
	// Get library clip
	library_clip = new clip(clip_id, sqlite);
	name = library_clip->getName();
	
	fetchLiveClip();
	
	cout << "CLIP: id:" << id << ", name:" << name << ", clip_id:" << clip_id << ", bar_start:" << bar_start << ", length:" << length << endl;
}


liveSequenceClip::liveSequenceClip(sequencerApp* _sequencer, liveSequenceClip* duplicate_clip) {
	sequencer = _sequencer;
	song = duplicate_clip->getSong();
	sqlite = sequencer->getSQLite();
	
	id = NULL;
	clip_id   = duplicate_clip->getClipId();
	track_id  = duplicate_clip->getTrackId();
	bar_start = duplicate_clip->getStart();
	length    = duplicate_clip->getLength();
	
	library_clip = duplicate_clip->getClip();
	name = library_clip->getName();
	
	fetchLiveClip();
}


void liveSequenceClip::fetchLiveClip() {
	if (sequencer->getClipMode() == "live") {
		live_clip = sequencer->getCurrentSet()->getClipByName(name);
	}
}


liveClip* liveSequenceClip::getLiveClip() {
	return live_clip;
}


liveSequenceSong* liveSequenceClip::getSong() {
	return song;
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


int liveSequenceClip::getStart() {
	return bar_start;
}

void liveSequenceClip::setStart(int bar) {
	bar_start = bar;
}


int liveSequenceClip::getEnd() {
	return bar_start + length;
}


int liveSequenceClip::getLength() {
	return length;
}