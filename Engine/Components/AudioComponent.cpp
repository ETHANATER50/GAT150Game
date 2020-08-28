#include "pch.h"
#include "AudioComponent.h"
#include "Audio/Sound.h"
#include "Audio/AudioSystem.h"

namespace ew {
	void AudioComponent::create(void* data) {
		owner = static_cast<GameObject*>(data);
	}

	void AudioComponent::destroy() {
		channel.stop();
	}

	void AudioComponent::read(const rapidjson::Value& value) {
		json::get(value, "sound", soundName); 
		json::get(value, "loop", loop); 
		json::get(value, "playOnAwake", playOnAwake); 

		if (playOnAwake) { 
			play(); 
		}
	}

	void AudioComponent::update() {

	}

	void AudioComponent::play() {
		channel.stop();
		Sound* sound = owner->engine->getSystem<ew::ResourceManager>()->get<ew::Sound>(soundName, owner->engine->getSystem<ew::AudioSystem>());
		ASSERT_MSG((sound), "Could not find sound: " + soundName); 
		channel = sound->play(loop);
	}
	void AudioComponent::stop() { 
		channel.stop(); 
	}	

}

