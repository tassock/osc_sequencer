/*
 *  sequence.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 7/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "sequence.h"

sequence::sequence() {
	tracks[0] = new sequencerTrack();
	tracks[1] = new sequencerTrack();
}