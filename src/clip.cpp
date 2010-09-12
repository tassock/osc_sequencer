#include "clip.h"

// New constructor
clip::clip(sequencerApp* _sequencer, int _id, int _length, string _name) {
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	id = _id;
	length = _length;
	name = _name;
	franklinBook.loadFont("frabk.ttf", 11);
}


// Old constructor
clip::clip(int _id, ofxSQLite* _sqlite) {
	id = _id;
	sqlite = _sqlite;
	franklinBook.loadFont("frabk.ttf", 12);
	
	// Get name/live_id from database
	ofxSQLiteSelect sel = sqlite->select("length, live_id")
	.from("library_clips")
	.where("id", id)
	.execute().begin();
	while(sel.hasNext()) {
		length = sel.getInt();
		name = sel.getString();
		sel.next();
	}
	
	loadPatterns();
}


void clip::draw(int clipX, int clipY, bool selected) {
	int clipH = (length * BEAT_HEIGHT) - CLIP_PADDING;
	
	// Color
	int color = 0; // dynamic
	int background_color = 0x000000;
	if (selected) {
		color = ORANGE;
	} else {
		color = GREY;
	}
	
	// Border
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(color);
	ofRect(clipX, clipY, CLIP_WIDTH, clipH);
	ofFill();
	
	// Background
	ofSetColor(background_color);
	ofRect(clipX, clipY, CLIP_WIDTH, clipH);
	
	// Name
	ofSetColor(color);
	franklinBook.drawString(name, clipX, clipY + 13);
	//franklinBook.drawString(name + " s: " + ofToString(start), clipX, clipY + 15);
}


string clip::getName() {
	return name;
}

int clip::getLength() {
	return length;
}

int clip::getId() {
	return id;
}

int clip::getNumPatterns() {
	return num_patterns;
}

pattern * clip::getPattern(int index) {
	pattern * x = patterns[index];
	return x;
}

void clip::loadPatterns() {
	
	// select all that match pattern ids
	ofxSQLiteSelect sel = sqlite->select("id, name")
	.from("patterns")
	.where("clip_id", id)
	.execute().begin();
	
	// set results as instance variables
	int count = 0;
	while(sel.hasNext()) {
		int pattern_id = sel.getInt();
		string pattern_name = sel.getString();
		
		// store pattern in buffer
		patterns[count] = new pattern(pattern_id, pattern_name, sqlite);
		
		// next record
		count ++;
		sel.next();
	}
	
	// set pattern count
	num_patterns = count;
}