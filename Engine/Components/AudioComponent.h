#pragma once
#include "Component.h"
#include "Audio/AudioChannel.h"

namespace ew {
	class AudioComponent : public Component {
	public:

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual Object* clone() const override { return new AudioComponent{ *this }; }

		void read(const rapidjson::Value& value) override;

		virtual void update() override;

		void play();

		void stop();
		void setSoundName(const std::string& _soundName) { soundName = _soundName; }

	protected:
		std::string soundName;
		bool loop{ false };
		bool playOnAwake{ false };

		AudioChannel channel;
	};
}