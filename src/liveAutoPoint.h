/*
 *  liveAutoPoint.h
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _lIVE_AUTO_POINT
#define _lIVE_AUTO_POINT

#include "ofMain.h"
#include "ofxSQLiteHeaders.h"
#include "sequencerApp.h"
#include "liveUi.h"

//class sequencerApp;

class liveAutoPoint: public liveUi {

public:
	liveAutoPoint(sequencerApp* _sequencer, int _id, int _live_auto_lane_id, int _bar, float _fval, bool _selected);
	void draw(int x, int y);
	void mousePressed(int _x, int _y, int button);
	void mouseDragged(int _x, int _y, int button);
	void mouseReleased();
	int getId();
	int getBar();
	void setBar(int _bar);
	float getVal();
	void setVal(float _val);
	bool getDragging();
	void setSelected(bool _selected);
	void save();
	void destroy();
	
	int id;
	int live_auto_lane_id;
	int bar;
	float val;
	
	bool selected;
	bool dragging;
	
	sequencerApp* sequencer;
	ofxSQLite* sqlite;

};

#endif