/*
 *  liveAutoPoint.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveAutoPoint.h"

liveAutoPoint::liveAutoPoint(int _bar, float _fval) {
	bar = _bar;
	val = _fval;
	
	w = 8;
	h = 8;
	
	selected = false;
	dragging = false;
}


void liveAutoPoint::draw(int _x, int _y) {
	x = _x;
	y = _y;
	if (selected) {
		ofSetColor(256, 256, 256);
	} else {
		ofSetColor(128, 128, 128);
	}
	//ofRect(x, y, w, h);
	//ofSetColor(256, 256, 256);
	ofCircle(x + (w/2), y + (h/2), (h/2));
}


void liveAutoPoint::mousePressed(int _x, int _y, int button) {
	if ( mouseInside(_x, _y) ) {
		selected = true;
		dragging = true;
		cout << "liveAutoPoint!!!" << endl;
	}
}


void liveAutoPoint::mouseDragged(int _x, int _y, int button) {
//	if ( mouseInside(_x, _y) ) {
//		
//		
//		cout << "DRAG!!!" << endl;
//	}
}


void liveAutoPoint::mouseReleased() {
	cout << "RELEASE!!!" << endl;
	dragging = false;
}


int liveAutoPoint::getBar() {
	return bar;
}


float liveAutoPoint::getVal() {
	return val;
}


void liveAutoPoint::setVal(float _val) {
	val = _val;
}


bool liveAutoPoint::getDragging() {
	return dragging;
}