/*
 *  liveAutoLane.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveAutoLane.h"

liveAutoLane::liveAutoLane(sequencerApp* _sequencer, int _id, int _x, int _y) {
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	id = _id;
	x = _x;
	y = _y;
	w = 140;
	h = 1000;
	
	last_click_x = 0;
	last_click_y = 0;
	
	range = 132;
	
//	points.insert ( points.end(), new liveAutoPoint(0, 0.5) );
//	points.insert ( points.end(), new liveAutoPoint(16, 0.5) );
	loadPoints();
}


void liveAutoLane::loadPoints() {
	// select all that match sequence id
	ofxSQLiteSelect sel = sqlite->select("id, bar, val")
	.from("live_auto_points")
	.where("live_auto_lane_id", id)
	.execute().begin();
	
	// set results as instance variables
	while(sel.hasNext()) {
		int point_id = sel.getInt();
		int bar = sel.getInt();
		float val = ofToFloat( sel.getString() );
		
		// store sequence clip in buffer
		points.insert ( points.end(), new liveAutoPoint(sequencer, point_id, id, bar, val, false) );
		
		// next record
		sel.next();
	}
}


void liveAutoLane::draw() {
	
	// Draw background
	ofSetColor(30, 30, 30);
	ofRect(x, y, w, h);
	
	// Draw lines
	if ( points.size() > 0 ) {
		for(int i = 0; i < points.size() - 1; i++) {
			liveAutoPoint* point_a = points[i];
			liveAutoPoint* point_b = points[i + 1];
			int x1 = x + (range * point_a->getVal() ) + 4;
			int y1 = y + (BEAT_HEIGHT * point_a->getBar() ) + 4;
			int x2 = x + (range * point_b->getVal() ) + 4;
			int y2 = y + (BEAT_HEIGHT * point_b->getBar() ) + 4;
			
			ofEnableSmoothing();
			ofSetColor(128, 128, 128);
			ofLine(x1, y1, x2, y2);
			ofDisableSmoothing();
		}
	}
	
	// Draw points
	for(int i = 0; i < points.size(); i++) {
		liveAutoPoint* s_point = points[i];
		int pointX = x + (range * s_point->getVal() );
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
		// Check for mouseover
		for(int i = 0; i < points.size(); i++) {
			points[i]->mousePressed(_x, _y, button);
		}
		// Check if last click coordinates are the same
		if (last_click_x == _x and last_click_y == _y) {
			// check if mouse is outside current points
			bool outside_points = true;
			for(int i = 0; i < points.size(); i++) {
				if ( points[i]->mouseInside(_x, _y) ) {
					outside_points = false;
					deleted_points.insert ( deleted_points.end(), new liveAutoPoint(sequencer, points[i]->getId(), id, points[i]->getBar(), points[i]->getVal(), false) );
					points.erase ( points.begin() + i );
				}
			}
			// create new point if it's outside
			if (outside_points) {
				cout << "CREATE NEW POINT" << endl;
				int new_bar = barFromY(_y - 4);
				float new_val = valFromX(_x - 4);
				// iterate through existing points to find valid spot
				int insert_point = 0;
				for(int i = 0; i < points.size(); i++) {
					if ( points[i]->getBar() < new_bar ) {
						insert_point = i + 1;
					}
				}
				points.insert ( points.begin() + insert_point, new liveAutoPoint(sequencer, NULL, id, new_bar, new_val, true) );
			}
		}
	}
	// Set last clicks
	last_click_x = _x;
	last_click_y = _y;
}


void liveAutoLane::mouseDragged(int _x, int _y, int button) {
	if ( mouseInside(_x, _y) ) {
		for(int i = 0; i < points.size(); i++) {
			if ( points[i]->getDragging() ) {
				// Set Val
				float x_dist = _x - x; 
				float new_val = valFromX(_x);
				if (x_dist <= (float)w) {
					points[i]->setVal(new_val);
				}
				// Set Bar if it's within range of relative points
				int new_bar = barFromY(_y);
				int new_min = 0;
				if ( i > 0 ) {
					new_min = points[i - 1]->getBar();
				}
				int new_max = 99999999;
				if ( i < points.size() - 1 ) {
					new_max = points[i + 1]->getBar();
				}
				if ( new_bar < new_min ) {
					points[i]->setBar(new_min);
				} else if ( new_bar > new_max ) {
					points[i]->setBar(new_max);
				} else {
					points[i]->setBar(new_bar);
				}
			}
		}
	}
}


void liveAutoLane::mouseReleased() {
	for(int i = 0; i < points.size(); i++) {
		points[i]->mouseReleased();;
	}
}


float liveAutoLane::valFromX(int _x) {
	float x_dist = _x - x; 
	float x_range = (float)range;
	return x_dist / x_range;
}


int liveAutoLane::barFromY(int _y) {
	int y_dist = _y - y; 
	return y_dist / BEAT_HEIGHT;
}


void liveAutoLane::save() {
	for(int i = 0; i < points.size(); i++) {
		points[i]->save();
	}
	for(int i = 0; i < deleted_points.size(); i++) {
		deleted_points[i]->destroy();
	}
}
	