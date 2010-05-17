#ifndef _CLIP
#define _CLIP

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "pattern.h"

#define NUM_PATTERNS 3

class clip {
	
public:
	clip(int _id, ofxSQLite* _sqlite);
	string getName();
	int getNumPatterns();
	pattern * getPattern(int index);
	void loadPatterns();
	
	int id;
	string name;
	pattern *patterns[NUM_PATTERNS];
	int num_patterns;
	
	ofxSQLite* sqlite;
	
};

#endif