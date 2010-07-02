/*
 *  sequence.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 7/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveSequence.h"

liveSequence::liveSequence() {
	tracks[0] = new liveSequenceTrack();
	tracks[1] = new liveSequenceTrack();
	name = "Peter";
}


string liveSequence::getName() {
	return name;
}

liveSequenceTrack * liveSequence::getTrack(int i) {
	return tracks[i];
}