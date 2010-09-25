/*
 *  liveAutoLane.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveAutoLane.h"

liveAutoLane::liveAutoLane(int _id, int _x, int _y) {
	id = _id;
	x = _x;
	y = _y;
	w = 100;
	h = 1000;
	
	range = 92;
	
	points.insert ( points.end(), new liveAutoPoint(0, 0.5) );
	points.insert ( points.end(), new liveAutoPoint(4, 0.5) );
}

void liveAutoLane::draw() {
	
	// Draw background
	ofSetColor(30, 30, 30);
	ofRect(x, y, w, h);
	
	// Draw points
	for(int i = 0; i < points.size(); i++) {
		liveAutoPoint* s_point = points[i];
		int pointX = x + (w * s_point->getVal() );
		int pointY = y + (BEAT_HEIGHT * s_point->getBar() );
		s_point->draw(pointX, pointY);
	}
}


void liveAutoLane::mousePressed(int _x, int _y, int button) {
	if ( mouseInside(_x, _y) ) {
		cout << "liveAutoLane!!!" << endl;
		for(int i = 0; i < points.size(); i++) {
			points[i]->mousePressed(_x, _y, button);
		}
	}
}


void liveAutoLane::mouseDragged(int _x, int _y, int button) {
	if ( mouseInside(_x, _y) ) {
		for(int i = 0; i < points.size(); i++) {
			if ( points[i]->getDragging() ) {
				// Set Val
				float x_dist = _x - x; 
				float x_range = (float)w;
				float new_val = x_dist / x_range;
				if (x_dist <= (float)range) {
					cout << "new_val: " << new_val << endl;
					points[i]->setVal(new_val);
				}
				// Set Bar
				int y_dist = _y - y; 
				int new_bar = y_dist / BEAT_HEIGHT;
				cout << "new_bar: " << new_bar << endl;
				points[i]->setBar(new_bar);
			}
		}
	}
}


void liveAutoLane::mouseReleased() {
	for(int i = 0; i < points.size(); i++) {
		points[i]->mouseReleased();;
	}
}