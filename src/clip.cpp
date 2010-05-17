#include "clip.h"

clip::clip(int _id, ofxSQLite* _sqlite) {
	id = _id;
	sqlite = _sqlite;
	name = "clip_" + ofToString( id );
	loadPatterns();
	cout << "!! NUM PATTERNS:" << num_patterns << endl;
}

string clip::getName() {
	return name;
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