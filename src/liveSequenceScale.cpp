/*
 *  liveSequenceScale.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveSequenceScale.h"

liveSequenceScale::liveSequenceScale(sequencerApp* _sequencer, int _x, int _y) {
	sequencer = _sequencer;
	x = _x;
	y = _y;
	w = 70;
	h = TRACK_HEIGHT;
	
	drag_beat = 0;
	drag_point = 0;
	
	franklinBook.loadFont("frabk.ttf", 10);
}


void liveSequenceScale::draw(int beat, int step) {
	
	int s = y - (beat * BEAT_HEIGHT) - (step * BEAT_HEIGHT / 32);
	
	// Background
//	ofSetColor(30, 30, 30);
//	ofRect(x, y, w, h);
	
	int draw_y = s;
	int _beat = 0;
	int _sub_beat = 4;
	ofSetLineWidth(1);
	while (draw_y < y + h) {
		
		// Draw stitch
		ofSetColor(35, 35, 35);
		ofLine(x, draw_y, x + 10, draw_y);
		
		// Draw label
		if (_sub_beat == 4) {
			ofSetColor(70, 70, 70);
			ofLine(x, draw_y, x + 10, draw_y);
			franklinBook.drawString( ofToString(_beat), x + 10, draw_y + 2);
			_sub_beat = 0;
		}
		
		// Increment iterators
		draw_y = draw_y + BEAT_HEIGHT;
		_beat ++;
		_sub_beat ++;
	}
}


void liveSequenceScale::mousePressed(int _x, int _y, int button) {
	if ( mouseInside(_x, _y) ) {
		drag_beat = sequencer->getStartBeat();
		drag_point = _y;
	}
	
}


void liveSequenceScale::mouseDragged(int _x, int _y, int button) {
	if (drag_beat == 0 and drag_point == 0) {
	} else {
	
		int beats_dragged = (drag_point - _y) / BEAT_HEIGHT;
		int new_beat = drag_beat + beats_dragged;
		if (new_beat >= 0) {
			sequencer->setStartBeat(new_beat);
		}
	
	}
}


void liveSequenceScale::mouseReleased() {
	drag_beat = 0;
	drag_point = 0;
}