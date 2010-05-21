/*
 *  graph.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 5/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "graph.h"

//--------------------------------------------------------------
graph::graph(int _x, int _y, int _w, int _h, sequencerApp* _sequencer) {
	
	graphX = _x;
	graphY = _y;
	graphW = _w;
	graphH = _h;
	sequencer = _sequencer;
	
	selectedBeat = 0;
	selectedStep = 0;
	
	graphColW = 4;
	graphColPad = 1;
	graphBeats = 4;
	
	cursorMode = "select"; // "select", "draw"
	highlightStart = 5;
	highlightEnd = 15;
	
	clearStepClipBoard();
	
}


//--------------------------------------------------------------
void graph::draw(){
	ofSetColor(255, 255, 255);
	ofRect(graphX, graphY, graphW, graphH);
	
	for ( int b=0; b<NUM_BEATS; b++ ) {
		for ( int s=0; s<NUM_STEPS; s++ ) {
			
			int num = (b * NUM_STEPS) + s;
			
			// Draw Graph
			int xDrawPoint = ((b * NUM_STEPS) + s) * (graphColPad + graphColW);
			float val = sequencer->getSParam()->getStepValue(b, s) * graphH;
			if (b == selectedBeat and s == selectedStep) {
				// step selected
				ofSetColor(204, 102, 0);
			} else if (b == sequencer->getBeat() and s == sequencer->getStep()) {
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
			
			
			// Draw highlightStart and highlightEnd
			if (num == highlightStart || num == highlightEnd) {
				ofSetColor(204, 102, 0);
				ofRect(xDrawPoint, graphY, 1, graphH + 20);
			}
			
		}
	}
	
}


//--------------------------------------------------------------
void graph::drawAxis(string marker, int height, int x, int y) {
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
void graph::mousePressed(int x, int y, int button) {
	setHighlightStart();
	editStep();
}


//--------------------------------------------------------------
void graph::editStep() {
	if (cursorMode == "draw") {
		float val = (float) (graphH - sequencer->getMouseY()) / graphH;
		selectedBeat = mouseStep() / NUM_STEPS;
		selectedStep = mouseStep() % NUM_STEPS;
		sequencer->getSParam()->setStepValue(selectedBeat, selectedStep, val);
	}
}
	


//--------------------------------------------------------------//
void graph::mouseDragged(int x, int y, int button) {
	setHighlightEnd();
	editStep();
}


//--------------------------------------------------------------
void graph::mouseReleased() {
	setHighlightEnd();
}


//--------------------------------------------------------------
// Returns the step number the mouse is over
int graph::mouseStep() {
	return sequencer->getMouseX() / 5;
}


//--------------------------------------------------------------
// sets highlightStart to the current step (GRAPH)
void graph::setHighlightStart() {
	if (cursorMode == "select") {
		highlightStart = mouseStep();
		highlightEnd = mouseStep(); // Reset ending
	}
}


//--------------------------------------------------------------
// sets highlightEnd to the current step (GRAPH)
void graph::setHighlightEnd() {
	if (cursorMode == "select") {
		highlightEnd = mouseStep();
	}
}


//--------------------------------------------------------------
void graph::keyPressed(int key) {

	// enter draw mode
	if ( key =='d' || key == 'D' ) {
		if (cursorMode != "draw") {
			cursorMode = "draw";
		}
	}
}


//--------------------------------------------------------------
void graph::keyReleased (int key) {
	
	// exit draw mode
	if ( key =='d' || key == 'D' ) {
		cursorMode = "select";
	} 
	
	// Copy selected area to clipboard
	else if ( key =='c' || key == 'C' ) {
		setStepClipBoard();
	}
	
	// Paste clipboard 
	else if ( key =='v' || key == 'R' ) {
		pasteStepClipBoard();
	}
	
}


//--------------------------------------------------------------
// sets stepClipBoard to bunk value that won't be pasted
void graph::clearStepClipBoard() {
	for ( int i=0; i<(NUM_STEPS * NUM_BEATS); i++ ) {
		stepClipBoard[i] = 100.0;
	}
}


//--------------------------------------------------------------
// sets stepClipBoard to values between highlightStart and highlightEnd
void graph::setStepClipBoard() {
	clearStepClipBoard();
	int s = highlightStart;
	while (s < highlightEnd) {
		stepClipBoard[s - highlightStart] = sequencer->getSParam()->getStepValue2(s);
		s ++;
	}
	//	// Log what's in the clipboard
	//	for ( int i=0; i<(NUM_STEPS * NUM_BEATS); i++ ) {
	//		if ( stepClipBoard[i] != 100.0 ) {
	//			cout << "stepClipBoard: #" << i << ", " << ofToString( stepClipBoard[i] ) << endl;
	//		}
	//	}
}


//--------------------------------------------------------------
// paste the clipboard into the current param, starting at the highlightStart
void graph::pasteStepClipBoard() {
	int s = highlightStart;
	for ( int i=0; i<(NUM_STEPS * NUM_BEATS); i++ ) {
		// Value is not bunk, step fits inside the param
		if (( stepClipBoard[i] != 100.0 ) and (s <= (NUM_STEPS * NUM_BEATS) - 1)) {
			sequencer->getSParam()->setStepValue2(s, stepClipBoard[i]);
		}
		s ++;
	}
}