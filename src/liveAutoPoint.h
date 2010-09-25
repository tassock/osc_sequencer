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
#include "liveUi.h"

class liveAutoPoint: public liveUi {

public:
	liveAutoPoint(int _bar, float _val);
	void draw(int x, int y);
	void mousePressed(int _x, int _y, int button);
	void mouseDragged(int _x, int _y, int button);
	void mouseReleased();
	int getBar();
	void setBar(int _bar);
	float getVal();
	void setVal(float _val);
	bool getDragging();
	
	int bar;
	float val;
	
	bool selected;
	bool dragging;

};

#endif