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
#include "liveSequence.h"

class sequencerApp;

class liveSequenceScale: public liveUi {

public:
	liveSequenceScale(int _x, int _y);
	void draw(int beat, int step);

};

#endif