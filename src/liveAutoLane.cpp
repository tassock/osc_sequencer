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
	
	// Draw lines
	for(int i = 0; i < points.size() - 1; i++) {
		liveAutoPoint* point_a = points[i];
		liveAutoPoint* point_b = points[i + 1];
		int x1 = x + (w * point_a->getVal() ) + 4;
		int y1 = y + (BEAT_HEIGHT * point_a->getBar() ) + 4;
		int x2 = x + (w * point_b->getVal() ) + 4;
		int y2 = y + (BEAT_HEIGHT * point_b->getBar() ) + 4;
		
		ofEnableSmoothing();
		ofSetColor(128, 128, 128);
		ofLine(x1, y1, x2, y2);
		ofDisableSmoothing();
	}
	
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
		// De-select all
		for(int i = 0; i < points.size(); i++) {
			points[i]->setSelected(false);
		}
		// check for mouseover
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