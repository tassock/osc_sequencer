#include "liveSequenceTrack.h"

liveSequenceTrack::liveSequenceTrack() {
	clips[0] = new liveSequenceClip(0,3);
	clips[1] = new liveSequenceClip(7,11);
}


liveSequenceClip* liveSequenceTrack::getClip(int i) {
	return clips[i];
}