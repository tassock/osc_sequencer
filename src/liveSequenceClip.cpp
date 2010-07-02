#include "liveSequenceClip.h"

liveSequenceClip::liveSequenceClip(int _start, int _end) {
	start = _start;
	end = _end;
}


int liveSequenceClip::getStart() {
	return start;
}


int liveSequenceClip::getEnd() {
	return end;
}


int liveSequenceClip::getLength() {
//	cout << "start" << ofToString(start) << endl;
//	cout << "end" << ofToString(end) << endl;
	return end - start;
}