#ifndef _PATTERN
#define _PATTERN

#include <string>
#include "ofMain.h"
#include "param.h"
#include "ofxSQLiteHeaders.h"
#include "ofxXmlSettings.h"

#define NUM_PARAMS 9
#define NUM_BEATS 4
#define NUM_STEPS 32

class pattern {
	
	public:
	pattern(int _id, string _name, ofxSQLite* _sqlite);
	string getName();
	param * getParam(int index);
	void loadParams();
	void loadXml();
	
	param *params[NUM_PARAMS];
	string param_names[NUM_PARAMS];
	string name;
	int id;
	ofxSQLite* sqlite;
	float paramBuffer[NUM_BEATS][NUM_STEPS];
	
	ofxXmlSettings XML;
	
};

#endif	
