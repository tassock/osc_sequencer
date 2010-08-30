#ifndef _CLIP
#define _CLIP

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "pattern.h"
#include "sequencerApp.h"

#define NUM_PATTERNS 3

class sequencerApp;

class clip {
	
public:
	clip(sequencerApp* _sequencer, int _id, int _length, string _name);
	clip(int _id, ofxSQLite* _sqlite);
	void draw(int clipX, int clipY, bool selected);
	string getName();
	int getLength();
	int getId();
	int getNumPatterns();
	pattern * getPattern(int index);
	void loadPatterns();
	
	int id;
	int length;
	string name;
	pattern *patterns[NUM_PATTERNS];
	int num_patterns;
	
	ofxSQLite* sqlite;
	sequencerApp* sequencer;
	ofTrueTypeFont  franklinBook;
	
};

#endif