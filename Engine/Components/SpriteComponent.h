#pragma once

#include "RenderComponent.h"


namespace ew {
	class SpriteComponent : public RenderComponent {
	public:

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;

		void read(const rapidjson::Value& value) override;

		virtual void update() override;
		virtual void draw() override;


	protected:
		SDL_Rect rect;
		std::string textureName;

	};
}