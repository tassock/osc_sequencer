#ifndef _CLIP
#define _CLIP

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"

class clip {
	
public:
	clip(int _id, ofxSQLite* _sqlite);
	string getName();
	
	int id;
	string name;
	
	ofxSQLite* sqlite;
	
};

#endif