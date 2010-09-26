/*
 *  liveAutoPoint.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveAutoPoint.h"

liveAutoPoint::liveAutoPoint(sequencerApp* _sequencer, int _id, int _live_auto_lane_id, int _bar, float _fval, bool _selected) {
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	id = _id;
	live_auto_lane_id = _live_auto_lane_id;
	bar = _bar;
	val = _fval;
	
	w = 8;
	h = 8;
	
	if (_selected) {
		selected = true;
		dragging = true;
	} else {
		selected = false;
		dragging = false;
	}
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
	dragging = false;
}


int liveAutoPoint::getId() {
	return id;
}


int liveAutoPoint::getBar() {
	return bar;
}


void liveAutoPoint::setBar(int _bar) {
	bar = _bar;
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


void liveAutoPoint::setSelected(bool _selected) {
	selected = _selected;
}


void liveAutoPoint::save() {
	cout << "SAVING POINT" << endl;
	
	if (id == NULL) {
		// Save self
		sqlite->insert("live_auto_points")
		.use("live_auto_lane_id", live_auto_lane_id)
		.use("bar", bar)
		.use("val", val)
		.execute();
		// Set id
		id = sqlite->lastInsertID();
	} else {
		// Update self
		sqlite->update("live_auto_points")
		.use("bar", bar)
		.use("val", val)
		.where("id", id)
		.execute();
	}
}

void liveAutoPoint::destroy() {
	sqlite->remove("live_auto_points")
	.where("id", id )
	.execute();
}