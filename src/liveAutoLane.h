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
#include "liveAutoPoint.h"

class liveAutoLane: public liveUi {

public: 
	liveAutoLane(int _id, int _x, int _y);
	void draw();
	void mousePressed(int _x, int _y, int button);
	void mouseDragged(int _x, int _y, int button);
	void mouseReleased();
	
	int id;
	
	int range;
	
	vector<liveAutoPoint*> points;

};

#endif