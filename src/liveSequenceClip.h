#ifndef _LIVE_SEQUENCER_CLIP
#define _LIVE_SEQUENCER_CLIP

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "liveClip.h"
#include "clip.h"
#include "sequencerApp.h"
#include "liveSequenceSong.h"

class clip;
class sequencerApp;
class liveSequenceSong;

class liveSequenceClip {
	
public:
	liveSequenceClip(sequencerApp* _sequencer, liveSequenceSong* _song, int _id, int _clip_id, int _track_id, int _sequence_song_order, int _length);
	liveSequenceClip(sequencerApp* _sequencer, liveSequenceClip*, int _id);
	liveSequenceClip(sequencerApp* _sequencer, liveSequenceSong* _song, clip* _clip, int _sequence_song_order);
	void save();
	void destroy();
	void fetchLiveClip();
	liveClip* getLiveClip();
	liveSequenceSong* getSong();
	clip* getClip();
	int getId();
	int getClipId();
	int getTrackId();
	string getName();
	int getOrder();
	void setOrder(int _order);
	int getLength();
	
	sequencerApp* sequencer;
	liveSequenceSong* song;
	ofxSQLite* sqlite;
	clip* library_clip;
	liveClip* live_clip;
	int id;
	int clip_id;
	int track_id;
	int sequence_song_order;
	int length;
	string name;
	
};

#endif