#ifndef _PARAM
#define _PARAM

#include <string>
#include "ofMain.h"
#include "ofxSQLiteHeaders.h"

#define VAL_LENGTH 128
#define NUM_BEATS 4
#define NUM_STEPS 32

class param {
	
	public:
		param(int _id, string _name, float _values[NUM_BEATS][NUM_STEPS], ofxSQLite* _sqlite);
		
		int fetch(int paramId);
		void save();
		string getName();
		float getStepValue(int beat, int step);
		void setStepValue(int beat, int step, float val);
		
		string name;
		int id;
		float values[NUM_BEATS][NUM_STEPS];
	
		ofxSQLite* sqlite; // maybe I can point to one instead of create new ones? 
	
};

#endif	
