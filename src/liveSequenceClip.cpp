#include "liveSequenceClip.h"

liveSequenceClip::liveSequenceClip(ofxSQLite* _sqlite, int _id, int _clip_id, int _track_id, int _bar_start, int _length) {
	sqlite = _sqlite;
	id = _id;
	clip_id = _clip_id;
	track_id = _track_id;
	bar_start = _bar_start;
	length = _length;
	
	// Get library clip
	library_clip = new clip(clip_id, sqlite);
	
	cout << "CLIP: id: " << id << ", clip_id:" << clip_id << ", bar_start:" << bar_start << ", length:" << length << endl;
	// find clip by id and load into buffer.
}


int liveSequenceClip::getTrackId() {
	return track_id;
}


int liveSequenceClip::getStart() {
	return bar_start;
}


int liveSequenceClip::getEnd() {
	return bar_start + length;
}


int liveSequenceClip::getLength() {
	return length;
}