/*
 *  liveAutoLane.h
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _lIVE_AUTO_LANE
#define _lIVE_AUTO_LANE

#include "ofMain.h"
#include "liveUi.h"
#include "liveSequence.h"
#include "sequencerApp.h"
#include "liveAutoPoint.h"

class liveAutoPoint;
class sequencerApp;

class liveAutoLane: public liveUi {

public: 
	liveAutoLane(sequencerApp* _sequencer, int _id, int _x, int _y);
	void loadPoints();
	void draw(int beat, int step);
	void update(int beat, int step);
	float getCurrentValue(int beat, int step);
	void mousePressed(int _x, int _y, int button);
	void mouseDragged(int _x, int _y, int button);
	void mouseReleased();
	float valFromX(int _x);
	int barFromY(int _y);
	void save();
	
	int id;
	
	int last_click_x;
	int last_click_y;
	
	int range;
	
	int s; // pixel height of bar 0
	
	string name;
	float val;
	
	vector<liveAutoPoint*> points;
	vector<liveAutoPoint*> deleted_points;
	
	sequencerApp* sequencer;
	ofxSQLite* sqlite;

};

#endif