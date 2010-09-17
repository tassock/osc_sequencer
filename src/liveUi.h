/*
 *  liveUi.h
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _LIVE_UI
#define _LIVE_UI

#include "ofMain.h"

class sequencerApp;

class liveUi {

public: 
	void mousePressed(int _x, int _y, int button);
	bool mouseInside(int mouseX, int mouseX);
	int getX();
	int getY();
	int getW();
	int getH();
	
	int x;
	int y;
	int w;
	int h;

};

#endif