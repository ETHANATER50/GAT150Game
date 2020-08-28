#include "pch.h"
#include "AudioSystem.h"

namespace ew {
	bool AudioSystem::startup() {
		FMOD_RESULT result = FMOD::System_Create(&system);
		ASSERT_MSG(result == FMOD_OK, "Error initializing FMOD system");

		void* extraDriverData = nullptr;
		result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
		ASSERT_MSG(result == FMOD_OK, "Error initializing FMOD system");

		return true;
	}

	void AudioSystem::shutdown() {
		FMOD_RESULT result = system->close();
		ASSERT_MSG(result == FMOD_OK, "Error closing FMOD system");

		result = system->release();
		ASSERT_MSG(result == FMOD_OK, "Error releasing FMOD system");
	}

	void AudioSystem::update() {
		FMOD_RESULT result = system->update();        
		ASSERT_MSG(result == FMOD_OK, "Error updating FMOD system.");
	}

}

