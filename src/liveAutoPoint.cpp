/*
 *  liveAutoPoint.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveAutoPoint.h"

liveAutoPoint::liveAutoPoint(sequencerApp* _sequencer, int _id, int _auto_lane_id, int _bar, float _fval, int _point_order, bool _selected) {
	sequencer = _sequencer;
	sqlite = sequencer->getSQLite();
	id = _id;
	auto_lane_id = _auto_lane_id;
	bar = _bar;
	val = _fval;
	point_order = _point_order;
	
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


void liveAutoPoint::setOrder(int _point_order) {
	point_order = _point_order;
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
		sqlite->insert("auto_points")
		.use("auto_lane_id", auto_lane_id)
		.use("bar", bar)
		.use("val", val)
		.use("point_order", point_order)
		.execute();
		// Set id
		id = sqlite->lastInsertID();
	} else {
		// Update self
		sqlite->update("auto_points")
		.use("bar", bar)
		.use("val", val)
		.use("point_order", point_order)
		.where("id", id)
		.execute();
	}
}

void liveAutoPoint::destroy() {
	sqlite->remove("auto_points")
	.where("id", id )
	.execute();
}