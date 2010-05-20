#include "param.h"

//--------------------------------------------------------------
param::param(int _id, int _pattern_id, string _name, ofxSQLite* _sqlite) {
	
	id = _id;
	pattern_id = _pattern_id;
	name = _name;
	sqlite = _sqlite;
	
	if (id == 0) {
		
		// create default values
		for ( int b=0; b<NUM_BEATS; b++ ) {
			for ( int s=0; s<NUM_STEPS; s++ ) {
				values[b][s] = 0.0;
			}
		}
		
		save();
		
	} else {
		
		// load existing values
		ofxSQLiteSelect sel = sqlite->select("step_data")
			.from("params")
			.where("id", id)
		.execute().begin();
		while(sel.hasNext()) {
			string step_data = sel.getString();
			
			//  parse step_data into values
			char * str = new char[step_data.size() + 1];
			std::strcpy ( str, step_data.c_str() );
			char * pch;
			pch = strtok (str," ");
			int b = 0;
			int s = 0;
			while (pch != NULL)
			{
				values[b][s] = ofToFloat( pch );
				s ++;
				if (s >= NUM_STEPS) {
					s = 0;
					b++;
				}
				pch = strtok (NULL, " ");
			}
			sel.next();
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
float param::getStepValue2(int step) {
	int b = step / NUM_STEPS;
	int s = step % NUM_STEPS;
	return values[b][s];
}


//--------------------------------------------------------------
void param::setStepValue(int beat, int step, float val) {
	values[beat][step] = val;
}


//--------------------------------------------------------------
void param::setStepValue2(int step, float val) {
	int b = step / NUM_STEPS;
	int s = step % NUM_STEPS;
	values[b][s] = val;
}


//--------------------------------------------------------------
// Save buffered values to database record. 
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
			.use("pattern_id",pattern_id)
			.use("step_data",stepData)
		.execute();
		
		id = sqlite->lastInsertID();
	} 
	
	// update record
	else {
		cout << " update record: " << id <<endl;
		
		sqlite->update("params")
			.use("name", name)
			.use("pattern_id",pattern_id)
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
