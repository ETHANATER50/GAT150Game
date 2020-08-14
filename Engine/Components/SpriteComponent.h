#pragma once

#include "RenderComponent.h"


namespace ew {
	class SpriteComponent : public RenderComponent {
	public:

		virtual void create(void* data = nullptr) override;
		virtual void destroy() override;

		virtual void update() override;
		virtual void draw() override;

	protected:
		class Texture* texture;

	};
}