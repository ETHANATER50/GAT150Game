#include "pch.h"
#include "Sound.h"
#include "AudioSystem.h"

namespace ew {
	bool Sound::create(const std::string& name, void* audioSystem) {
		system = static_cast<AudioSystem*>(audioSystem)->system;
		FMOD_RESULT result = system->createSound(name.c_str(), FMOD_DEFAULT, 0, &sound);
		ASSERT_MSG(result == FMOD_OK, "Error creating sound: " + name);

		return true;
	}

	void Sound::destroy() {
		if (sound) {
			sound->release();
		}
	}

	AudioChannel Sound::play(bool loop) {
		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;        
		sound->setMode(mode);    

		FMOD::Channel* channel;       
		FMOD_RESULT result = system->playSound(sound, 0, false, &channel);        
		ASSERT_MSG(result == FMOD_OK, "Error playing FMOD sound.");        
		
		return AudioChannel{ channel };
	}

}

