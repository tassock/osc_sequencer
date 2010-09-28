/*
 *  liveSequenceScale.cpp
 *  osc_sequencer
 *
 *  Created by Peter Marks on 9/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "liveSequenceScale.h"

liveSequenceScale::liveSequenceScale(int _x, int _y) {
	x = _x;
	y = _y;
	w = 40;
	h = 1000;
	
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