/*
 *  liveUi.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveUi.h"

//--------------------------------------------------------------
void liveUi::mousePressed(int _x, int _y, int button) {
	cout << "DEFAULT" << endl;
}


//--------------------------------------------------------------
bool liveUi::mouseInside(int mouse_X, int mouse_Y) {
	
	if (mouse_X > x and mouse_X <= x + w and mouse_Y > y and mouse_Y <= y + h) {
		return true;
	} else {
		return false;
	}
}


//--------------------------------------------------------------
int liveUi::getX() {
	return x;
}


//--------------------------------------------------------------
int liveUi::getY() {
	return y;
}


//--------------------------------------------------------------
int liveUi::getW() {
	return w;
}


//--------------------------------------------------------------
int liveUi::getH() {
	return h;
}