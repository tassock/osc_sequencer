#include "clip.h"

clip::clip(int _id, ofxSQLite* _sqlite) {
	id = _id;
	sqlite = _sqlite;
	name = "clip_" + ofToString( id );
}

string clip::getName() {
	return name;
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
		patterns[count] = new pattern(pattern_name, sqlite);
		
		// next record
		count ++;
		sel.next();
	}
}