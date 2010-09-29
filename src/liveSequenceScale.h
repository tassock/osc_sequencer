/*
 *  liveSequenceScale.h
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _lIVE_SEQUENCE_SCALE
#define _lIVE_SEQUENCE_SCALE

#include "ofMain.h"
#include "liveUi.h"
#include "sequencerApp.h"
#include "liveSequence.h"

class sequencerApp;

class liveSequenceScale: public liveUi {

public:
	liveSequenceScale(sequencerApp* _sequencer, int _x, int _y);
	void draw(int beat, int step);
	void mousePressed(int _x, int _y, int button);
	void mouseDragged(int _x, int _y, int button);
	void mouseReleased();
	
	int drag_beat;
	int drag_point;
	
	sequencerApp* sequencer;

};

#endif