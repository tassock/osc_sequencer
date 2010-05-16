#include "clip.h"

clip::clip(int _id, ofxSQLite* _sqlite) {
	id = _id;
	sqlite = _sqlite;
	name = "clip_" + ofToString( id );
}

string clip::getName() {
	return name;
}