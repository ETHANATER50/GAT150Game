#pragma once
#include <fmod.hpp>

namespace ew {
	class AudioChannel {
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* _channel) : channel{ _channel } {}

		bool isPlaying();
		void stop();

	protected:
		FMOD::Channel* channel{ nullptr };
	};
}