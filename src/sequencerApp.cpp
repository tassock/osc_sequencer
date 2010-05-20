#include "sequencerApp.h"

//--------------------------------------------------------------
void sequencerApp::setup(){
	
	ofBackground( 0, 0, 0 );
	initDatabase();
	
	// Set Defaults
	beat = 0; // might need to adjust this with real data
	step = 0;
	selectedBeat = 0;
	selectedStep = 0;
	gainSliderValue = 0.0;
	scaleSliderValue = 0.0;
	
	windowW = 1060;
	windowH = 820;
	
	graphX = 0;
	graphY = 0;
	graphW = 640;
	graphH = 300;
	graphColW = 4;
	graphColPad = 1;
	graphBeats = 4;
	
	navItemW = 100; // 130
	navItemH = 20;
	navItemXPad = 5;
	navItemYPad = 15;
	
	// Create sliders
	gainSlider  = new slider("gain",  graphX + graphW, 0);
	scaleSlider = new slider("scale", graphX + graphW + 60, 0);
	
	clipNavX = graphX + graphW + 120;
	clipNavY = 0;
	clipNavW = navItemW;
	clipNavH = graphH;
	
	patternNavX = clipNavX + clipNavW;
	patternNavY = 0;
	patternNavW = navItemW;
	patternNavH = graphH;
	
	paramNavX = patternNavX + patternNavW;
	paramNavY = 0;
	paramNavW = navItemW;
	paramNavH = graphH;
	
	rWindowX = 0;
	rWindowY = 340;
	rWindowH = 480;
	rWindowW = 640;
	
	cursorMode = "select"; // "select", "draw"
	highlightStart = 5;
	highlightEnd = 15;

	
//	// open an outgoing connection to HOST:PORT
//	sender.setup( HOST, SEND_PORT );
	
	// listen on the given port
	receiver.setup( RECIEVE_PORT );
	
	// load clip buffer
	clipBuffer[0] = new clip(1, sqlite);
	clipBuffer[1] = new clip(2, sqlite);
	
	// set selected clip, pattern and param
	selectedClip = 0;
	selectedPattern = 0; //patternBuffer[0];
	selectedParam = 2;
	setSelectedParamsAndPatterns();
	
	// load xml (not working yet?)
	//patternBuffer[0]->loadXml();
	
	
	
//	// Load XML
//	message = "loading toxine.xml";
//	if( XML.loadFile("toxine.xml") ){
//		message = "toxine.xml loaded!";
//	}else{
//		message = "unable to load toxine.xml check data/ folder";
//	}
//	
//	// Load XML into paramBuffer
//	int numTags = XML.getNumTags("val");
//	int totalToRead = MIN( numTags, (NUM_BEATS * NUM_STEPS) );
//	for(int i = 0; i < totalToRead; i++){
//		paramBuffer[0] = ofToFloat( XML.getValue("val", "0.0", i) );
//		//sPattern->getParam(selectedParam)->setStepValue(selectedBeat, selectedStep, val);
//		//paramBuffer[i] = ofToFloat( XML.getValue("val", "0.0", i) );
//	}
	
//	// Load paramBuffer into database
//	string stepData = "";
//	for(int i = 0; i < (NUM_BEATS * NUM_STEPS); i++) {
//		stepData += " " + ofToString( paramBuffer[i] );
//	}
//	// cout << "stepData: " << stepData << endl;
//	sqlite->insert("params")
//		.use("name", "imported")
//		.use("pattern_id",1)
//		.use("step_data",stepData)
//	.execute();
	
	
//	// Load db entry into paramBuffer
//	ofxSQLiteSelect sel = sqlite->select("step_data")
//		.from("params")
//		.where("id", 1)
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
//		//cout << "pch: " << pch << endl;
//		paramBuffer[i] = ofToFloat( pch );
//		i ++;
//		pch = strtok (NULL, " ");
//	}
	
	
}


//--------------------------------------------------------------
void sequencerApp::initDatabase() {
	
	sqlite = new ofxSQLite("sequencer.db");
	sqlite->simpleQuery("" \
		"CREATE TABLE IF NOT EXISTS clips (" \
		" id INTEGER PRIMARY KEY AUTOINCREMENT," \
		" live_id TEXT," \
		" song_id INTEGER" \
		");"
	);
	
	sqlite->simpleQuery("" \
		"CREATE TABLE IF NOT EXISTS patterns (" \
		" id INTEGER PRIMARY KEY AUTOINCREMENT," \
		" name TEXT," \
		" clip_id INTEGER" \
		");"
	);
	
	sqlite->simpleQuery("" \
		"CREATE TABLE IF NOT EXISTS params (" \
		" id INTEGER PRIMARY KEY AUTOINCREMENT," \
		" name TEXT," \
		" pattern_id INTEGER," \
		" step_data TEXT" \
		");"
	);
	
	
//	// select
//	ofxSQLiteSelect sel = sqlite->select("live_id")
//		.from("clips")
//		.where("id", 2)
//	.execute().begin();
//	
//	while(sel.hasNext()) {
//		string live_id = sel.getString();
//		cout << "live_id: " << live_id << endl;
//		sel.next();
//	}
//	
//	
//	// TODO: Understand what str[] and * pch do
//	char str[] = "0.11 0.22 0.33";
//	char * pch;
//	pch = strtok (str," ");
//	while (pch != NULL)
//	{
//		cout << "pch: " << pch << endl;
//		pch = strtok (NULL, " ");
//	}
	
}


//--------------------------------------------------------------
void sequencerApp::update() {
	
	// Increment step
	step ++;
	if (step == NUM_STEPS) {
		step = 0;
	}
	
	// Recieve Data
	while( receiver.hasWaitingMessages() ) {
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		// Handle Beat
		// ToDo: pass second argument to adjust tempo and adjust framerate
		if ( m.getAddress() == "/bar_transport" ) {
			int arg = m.getArgAsInt32( 0 ) - 1;
			if (arg >= 0 and arg < NUM_BEATS) {
				beat = arg;
				step = 0;
			}
		}
	}
	
	// Send Data
//	ofxOscMessage m;
//	m.setAddress( "/test" );
//	for ( int pat=0; pat<( sClip->getNumPatterns() ); pat++ ) {
//		for ( int p=0; p<NUM_PARAMS; p++ ) {
//			m.addStringArg( ofToString( 
//				sClip->getPattern(pat)->getParam(p)->getStepValue(beat, step)
//			) );
//		}
//	}
//	sender.sendMessage( m );

}


//--------------------------------------------------------------
void sequencerApp::draw(){
	
	drawRenderWindow();
	drawGraph();
	drawSliders();
	drawClipNav();
	drawPatternNav();
	drawParamNav();
	
	// Display step
	string buf;
	buf = "step: " + ofToString( step );
	ofSetColor(255, 255, 255);
	ofDrawBitmapString( buf, 800, 400 );
	buf = "rate: " + ofToString( ofGetFrameRate() );
	ofDrawBitmapString( buf, 800, 420 );
	
}



//--------------------------------------------------------------
void sequencerApp::drawRenderWindow(){
	
	// Render params
	for ( int i=0; i<( sClip->getNumPatterns() ); i++ ) {
		
		// Define vars
		pattern * r_pattern = sClip->getPattern(i);
		float red    = r_pattern->getParam(0)->getStepValue(beat, step);
		float green  = r_pattern->getParam(1)->getStepValue(beat, step);
		float blue   = r_pattern->getParam(2)->getStepValue(beat, step);
		float alpha  = r_pattern->getParam(3)->getStepValue(beat, step);
		float height = r_pattern->getParam(4)->getStepValue(beat, step);
		float width  = r_pattern->getParam(5)->getStepValue(beat, step);
		float x      = r_pattern->getParam(6)->getStepValue(beat, step);
		float y      = r_pattern->getParam(7)->getStepValue(beat, step);
		float y_fill = r_pattern->getParam(8)->getStepValue(beat, step);
		
		// Define dimensions
		float _x = x * rWindowW;
		float _y = ((y + (height * (1.0 - y_fill))) * rWindowH) + rWindowY;
		float _w = width * rWindowW;
		float _h = (y_fill * height) * rWindowH;
		
//		// Render Rectangle
//		ofSetColor(red * 256, green * 256, blue * 256, alpha * 256 );
//		ofRect( _x, _y, _w, _h);
		
		// Render gradient rectangle
		glBegin(GL_QUADS);
		glColor4f(red, green, blue, alpha );
		glVertex2f(_x, _y); // top left
		glColor4f(red, green, blue, 0 );
		glVertex2f(_x, _y + _h); // bottom left
		glVertex2f(_x + _w, _y + _h); // bottom right
		glColor4f(red, green, blue, alpha );
		glVertex2f(_x + _w, _y); // top right
		glEnd();
		
	}
	
	// Clear outside window
	ofSetColor(0, 0, 0, 256 );
	ofRect(0, 0, windowW, windowH - rWindowH); // Clear Top
	ofRect(rWindowW, rWindowY, windowW - rWindowW, rWindowH); // Clear Right
}
	


//--------------------------------------------------------------
void sequencerApp::drawGraph(){
	ofSetColor(255, 255, 255);
	ofRect(graphX, graphY, graphW, graphH);
	
	for ( int b=0; b<NUM_BEATS; b++ ) {
		for ( int s=0; s<NUM_STEPS; s++ ) {
			
			int num = (b * NUM_STEPS) + s;
			
			// Draw Graph
			int xDrawPoint = ((b * NUM_STEPS) + s) * (graphColPad + graphColW);
			float val = sParam->getStepValue(b, s) * graphH;
			if (b == selectedBeat and s == selectedStep) {
				// step selected
				ofSetColor(204, 102, 0);
			} else if (b == beat and s == step) {
				// step playing
				ofSetColor(255, 255, 255);
			} else if (num >= highlightStart and num < highlightEnd) {
				// step selected
				ofSetColor(0, 204, 0);
			} else {
				ofSetColor(0, 102, 204);
			} 
			ofRect(1 + xDrawPoint, graphH - val, graphColW, val);
			
			// Draw Axis
			string marker;
			if (s == 0) {
				marker = ofToString(b + 1);
				drawAxis(marker, 15, xDrawPoint, graphH);
			} else if (s == 8) {
				marker = ofToString(b + 1) + ".2";
				drawAxis(marker, 5, xDrawPoint, graphH);
			} else if (s == 16) {
				marker = ofToString(b + 1) + ".3";
				drawAxis(marker, 5, xDrawPoint, graphH);
			} else if (s == 24) {
				marker = ofToString(b + 1) + ".4";
				drawAxis(marker, 5, xDrawPoint, graphH);
			}
			
		}
	}
	
}


//--------------------------------------------------------------
void sequencerApp::drawAxis(string marker, int height, int x, int y) {
	int shift = 0;
	if (height == 15) {
		ofSetColor(255, 255, 255);
		shift = 3;
	} else {
		ofSetColor(150, 150, 150);
		shift = 9;
	}
	ofRect(x, y, 1, height);
	ofDrawBitmapString( marker, x - shift, y + height + 14 );
}


//--------------------------------------------------------------
void sequencerApp::drawSliders() {
	
	gainSlider->draw();
	scaleSlider->draw();
	
}


//--------------------------------------------------------------
void sequencerApp::drawClipNav() {
	ofSetColor(100, 100, 100);
	ofRect(clipNavX, clipNavY, clipNavW, clipNavH);
	for ( int c=0; c<NUM_CLIPS; c++ ) {
		drawNavigationItem(
			clipNavX,					// x
			clipNavY + (c * navItemH),	// y
			clipBuffer[c]->getName(),	// name
			sClip == clipBuffer[c]		// selected
		);
	}
}


//--------------------------------------------------------------
void sequencerApp::drawPatternNav() {
	ofSetColor(100, 100, 100);
	ofRect(patternNavX, patternNavY, patternNavW, patternNavH);
	for ( int p=0; p<(sClip->getNumPatterns()); p++ ) {
		drawNavigationItem(
			patternNavX,				  // x
			patternNavY + (p * navItemH), // y
			sClip->getPattern(p)->getName(),  // name
			sPattern == sClip->getPattern(p)  // selected
		);
	}
}


//--------------------------------------------------------------
void sequencerApp::drawParamNav() {
	ofSetColor(100, 100, 100);
	ofRect(paramNavX, paramNavY, paramNavW, paramNavH);
	for ( int p=0; p<NUM_PARAMS; p++ ) {
		drawNavigationItem(
			paramNavX,							// x
			paramNavY + (p * navItemH),			// y
			sPattern->getParam(p)->getName(),	// name
			sParam == sPattern->getParam(p)		// selected
		);
	}
}


//--------------------------------------------------------------
void sequencerApp::drawNavigationItem(int x, int y, string name, bool selected) {
	ofSetColor(0, 0, 0);
	ofRect(x, y, navItemW, navItemH);
	if (selected) {
		ofSetColor(204, 102, 0);
	} else {
		ofSetColor(255, 255, 255);
	}
	ofDrawBitmapString( name, x + navItemXPad, y + navItemYPad );	
}


//--------------------------------------------------------------
void sequencerApp::keyPressed  (int key) {
	if ( key =='d' || key == 'D' ) {
		if (cursorMode != "draw") {
			// enter draw mode
			cursorMode = "draw";
			cout << cursorMode << endl;
		}
	} 
}

void sequencerApp::keyReleased (int key) {
	if ( key =='d' || key == 'D' ) {
		// exit draw mode
		cursorMode = "select";
		cout << cursorMode << endl;
	} 
}


//--------------------------------------------------------------
void sequencerApp::mousePressed(int x, int y, int button) {
	setSelected();
	setHighlightStart();
}


//--------------------------------------------------------------
void sequencerApp::mouseDragged(int x, int y, int button) {
	if ( gainSlider->isSelected() ) {
		gainSlider->setValueFromMouse(mouseY);
		setGainSliderValue();
	} else if ( scaleSlider->isSelected() ) {
		scaleSlider->setValueFromMouse(mouseY);
		setScaleSliderValue();
	}
	else {
		setSelected();
		setHighlightEnd();
	}
}

void sequencerApp::mouseReleased() {
	cout << "MY RELEASE" << endl;
	gainSlider->setSelected(0);
	scaleSlider->setSelected(0);
	setHighlightEnd();
}

//--------------------------------------------------------------
// Returns the step number the mouse is over
int sequencerApp::mouseStep() {
	return mouseX / 5;
}


//--------------------------------------------------------------
void sequencerApp::setSelected() {
	
	// Handle graph click
	if ( mouseInside(graphX, graphY, graphW, graphH) ) {
		
		// Change graph value
		if (cursorMode == "draw") {
			float val = (float) (graphH - mouseY) / graphH;
			selectedBeat = mouseStep() / NUM_STEPS;
			selectedStep = mouseStep() % NUM_STEPS;
			sPattern->getParam(selectedParam)->setStepValue(selectedBeat, selectedStep, val);
		}
	}
	
	// Handle clip nav click
	else if ( mouseInside(clipNavX, clipNavY, clipNavW, clipNavH) ) {
		int i = ( ( mouseY - clipNavY ) / navItemH );
		if (i < NUM_CLIPS) {
			resetSelectValues();
			selectedClip = i;
			setSelectedParamsAndPatterns();
		}
	}
	
	// Handle pattern nav click
	else if ( mouseInside(patternNavX, patternNavY, patternNavW, patternNavH) ) {
		int i = ( ( mouseY - patternNavY ) / navItemH );
		if (i < NUM_PATTERNS) {
			resetSelectValues();
			selectedPattern = i;
			setSelectedParamsAndPatterns();
		}
	}
		
	// Handle param nav click
	else if ( mouseInside(paramNavX, paramNavY, paramNavW, paramNavH) ) {
		int i = ( ( mouseY - paramNavY ) / navItemH );
		if (i < NUM_PARAMS) {
			sParam->save();
			resetSelectValues();
			selectedParam = i;
			setSelectedParamsAndPatterns();
		}
	}
	
	// Handle Gain Fader click
	else if ( gainSlider->mouseInsideFader(mouseX, mouseY) ) {
		cout << "gainSliderSelected" << endl;
		gainSlider->setSelected(1);
	}
	
	// Handle Scale Fader click
	else if ( scaleSlider->mouseInsideFader(mouseX, mouseY) ) {
		cout << "scaleSliderSelected" << endl;
		scaleSlider->setSelected(1);
	}
			 
}

//--------------------------------------------------------------
// sets highlightStart to the current step
void sequencerApp::setHighlightStart() {
	if (cursorMode == "select") {
		highlightStart = mouseStep();
		highlightEnd = mouseStep(); // Reset ending
	}
}


//--------------------------------------------------------------
// sets highlightEnd to the current step
void sequencerApp::setHighlightEnd() {
	if (cursorMode == "select") {
		highlightEnd = mouseStep();
	}
}


//--------------------------------------------------------------
// Sets selected param and pattern object pointers to selected indexes. 
void sequencerApp::setSelectedParamsAndPatterns() {
	sClip = clipBuffer[selectedClip];
	sPattern = sClip->getPattern(selectedPattern);
	sParam = sPattern->getParam(selectedParam);
}


//--------------------------------------------------------------
void sequencerApp::setGainSliderValue() {
	float old_gval = gainSliderValue;
	float new_gval = gainSlider->getValue();
	cout << " new_gval:" << new_gval << ", old_gval" << old_gval << endl;
	gainSliderValue = new_gval;
	for ( int b=0; b<NUM_BEATS; b++ ) {
		for ( int s=0; s<NUM_STEPS; s++ ) {
			float saved_val = sParam->getStepValue(b, s); // needs to be saved
			sParam->setStepValue(b, s, saved_val - old_gval + new_gval);
		}
	}
	
}


//--------------------------------------------------------------
void sequencerApp::setScaleSliderValue() {
	float old_gval = scaleSliderValue;
	float new_gval = scaleSlider->getValue();
	scaleSliderValue = new_gval;
	//cout << " new_gval:" << new_gval << endl;
	float saved_val = 0.0;
	float new_val = 0.0;
	for ( int b=0; b<NUM_BEATS; b++ ) {
		for ( int s=0; s<NUM_STEPS; s++ ) {
			saved_val = sParam->getStepValue(b, s); // needs to be saved
			new_val = saved_val * (1 + new_gval - old_gval);
			sParam->setStepValue(b, s, new_val);
		}
	}
	// cout << new_val << " = (" << saved_val << " / 1 + " << old_gval << ") * (1 + " << new_gval << ")" << endl;
	
}


//--------------------------------------------------------------
void sequencerApp::resetSelectValues() {
	selectedBeat = 0;
	selectedStep = 0;
	gainSlider->setValue(0);
	gainSliderValue = 0;
	scaleSlider->setValue(0);
	scaleSliderValue = 0;
}


//--------------------------------------------------------------
bool sequencerApp::mouseInside (int x, int y, int width, int height) {
	if (mouseX > x and mouseX <= x + width and mouseY > y and mouseY <= y + height) {
		return true;
	} else {
		return false;
	}

}