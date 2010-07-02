#include "sequencerTrack.h"

sequencerTrack::sequencerTrack() {
	clips[0] = new sequencerClip(0,3);
	clips[1] = new sequencerClip(7,11);
}