#include "param.h"

//--------------------------------------------------------------
param::param(int _id, string _name, float _values[NUM_BEATS][NUM_STEPS], ofxSQLite* _sqlite) {
	
	id = _id;
	name = _name;
	sqlite = _sqlite;
	
	// sqlite = new ofxSQLite("sequencer.db"); // maybe I can point to one instead of create new ones? 
	for ( int b=0; b<NUM_BEATS; b++ ) {
		for ( int s=0; s<NUM_STEPS; s++ ) {
			values[b][s] = _values[b][s];
		}
	}
}

//--------------------------------------------------------------
string param::getName() {
	return name;
}


//--------------------------------------------------------------
float param::getStepValue(int beat, int step) {
	return values[beat][step];
}


//--------------------------------------------------------------
void param::setStepValue(int beat, int step, float val) {
	values[beat][step] = val;
}


//--------------------------------------------------------------
void param::save() {
	
	// Parse step data into string
	string stepData = "";
	for ( int b=0; b<NUM_BEATS; b++ ) {
		for ( int s=0; s<NUM_STEPS; s++ ) {
			stepData += " " + ofToString( values[b][s] );
		}
	}
	// cout << "stepData: " << stepData << endl;
	
	// create record
	if (id == 0) {
		cout << " create record " << endl;
		sqlite->insert("params")
			.use("name", name)
			.use("pattern_id",1)
			.use("step_data",stepData)
		.execute();
	} 
	
	// update record
	else {
		cout << " update record: " << id <<endl;
		
		sqlite->update("params")
			.use("name", name)
			.use("pattern_id",1)
			.use("step_data",stepData)
			.where("id", id)
		.execute();
	}

}


//--------------------------------------------------------------
int param::fetch(int paramId) {
	
	return paramId + 1;
	
	//	ofxSQLiteSelect sel = sqlite->select("step_data")
	//	.from("params")
	//	.where("id", 1)
	//	.execute().begin();
	//	string step_data;
	//	while(sel.hasNext()) {
	//		step_data = sel.getString();
	//		// cout << "step_data: " << step_data << endl;
	//		sel.next();
	//	}
	//	// http://www.daniweb.com/forums/thread28946.html#
	//	char * str = new char[step_data.size() + 1];
	//	std::strcpy ( str, step_data.c_str() );
	//	
	//	char * pch;
	//	pch = strtok (str," ");
	//	int i = 0;
	//	while (pch != NULL)
	//	{
	//		cout << "pch: " << pch << endl;
	//		paramBuffer[i] = ofToFloat( pch );
	//		i ++;
	//		pch = strtok (NULL, " ");
	//	}
	
}
