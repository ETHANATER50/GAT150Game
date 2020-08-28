#pragma once
#include "Resources/Resource.h"
#include "AudioChannel.h"
#include <fmod.hpp>

namespace ew {
	class Sound : public Resource {
	public:

		virtual bool create(const std::string& name, void* data = nullptr) override;
		virtual void destroy() override;

		AudioChannel play(bool loop = false);

	private:
		FMOD::System* system{ nullptr };
		FMOD::Sound* sound{ nullptr };
	};
}