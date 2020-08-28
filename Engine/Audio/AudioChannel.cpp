#include "pch.h"
#include "AudioChannel.h"


namespace ew {
	bool AudioChannel::isPlaying() {
		bool isPlaying = false;
		if (channel) {
			channel->isPlaying(&isPlaying);
		}
		return isPlaying;
	}

	void AudioChannel::stop() {
		if (isPlaying()) {
			channel->stop();
		}
	}

}
