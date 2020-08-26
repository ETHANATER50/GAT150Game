#pragma once

#include "SpriteComponent.h"
namespace ew {
	class SpriteAnimationComponent : public SpriteComponent {
	public:
		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual Object* clone() const override { return new SpriteAnimationComponent{ *this }; }

		void read(const rapidjson::Value& value) override;

		virtual void update() override;

	protected:
		int frame{ 0 };
		float frameTimer{ 0 };
		float frameRate{ 0 };

		int numX{ 0 };
		int numY{ 0 };
		int frames{ 0 };
		int fps{ 1 };
	};
}