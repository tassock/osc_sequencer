#include "pattern.h"

pattern::pattern(int _id, string _name, ofxSQLite* _sqlite) {
	
	id = _id;
	name = _name;
	sqlite = _sqlite;
	loadParams();
	
}

string pattern::getName() {
	return name;
}

param * pattern::getParam(int index) {
	param * x = params[index];
	return x;
}

void pattern::loadParams() {
	
	// select all that match pattern ids
	ofxSQLiteSelect sel = sqlite->select("id, name")
		.from("params")
		.where("pattern_id", id)
	.execute().begin();
	
	// set results as instance variables
	int count = 0;
	while(sel.hasNext()) {
		int param_id = sel.getInt();
		string param_name = sel.getString();
//		string step_data = sel.getString();
//		
//		
//		//  parse step_data into paramBuffer
//		char * str = new char[step_data.size() + 1];
//		std::strcpy ( str, step_data.c_str() );
//		char * pch;
//		pch = strtok (str," ");
//		int b = 0;
//		int s = 0;
//		while (pch != NULL)
//		{
//			paramBuffer[b][s] = ofToFloat( pch );
//			s ++;
//			if (s >= NUM_STEPS) {
//				s = 0;
//				b++;
//			}
//			pch = strtok (NULL, " ");
//		}
		
		
		params[count] = new param(param_id, id, param_name, sqlite);
		// cout << "pattern_name: " << pattern_name << ", pattern_id: " << pattern_id << ", step_data: " << step_data << endl;
		count ++;
		sel.next();
	}
	
	// Load default params if none are found
	if ( count == 0 ) {
		
		param_names[0] = "red";
		param_names[1] = "green";
		param_names[2] = "blue";
		param_names[3] = "alpha";
		param_names[4] = "height";
		param_names[5] = "width";
		param_names[6] = "x";
		param_names[7] = "y";
		param_names[8] = "y_fill";
		
		for(int i = 0; i < NUM_PARAMS; i++){
			
			// create db record
			params[i] = new param(0, id, param_names[i], sqlite);
			
		}
	}
}


void pattern::loadXml() {
	// Load XML
	string message = "";
	message = "loading toxine.xml";
	if( XML.loadFile("toxine.xml") ){
		message = "toxine.xml loaded!";
	}else{
		message = "unable to load toxine.xml check data/ folder";
	}

	// Load XML into paramBuffer
	int numTags = XML.getNumTags("val");
	int totalToRead = MIN( numTags, (NUM_BEATS * NUM_STEPS) );
	int b = 0;
	int s = 0;
	for(int i = 0; i < totalToRead; i++){
		paramBuffer[b][s] = ofToFloat( XML.getValue("val", "0.0", i) );
		s ++;
		if (s >= NUM_STEPS) {
			s = 0;
			b++;
		}
		//sPattern->getParam(selectedParam)->setStepValue(selectedBeat, selectedStep, val);
		//paramBuffer[i] = ofToFloat( XML.getValue("val", "0.0", i) );
	}
}