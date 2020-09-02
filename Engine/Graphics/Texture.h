#pragma once

#include "Math/Vector2.h"
#include <SDL.h>
#include "Resources/Resource.h"
#include <string>


namespace ew {
	class Texture : public Resource{
	public:
		bool create(const std::string& name, void* _renderer) override;
		void destroy() override;

		void draw(const Vector2& position, float angle = 0, const Vector2 & scale = { 1, 1 }, const Vector2 & origin = Vector2::zero, bool flip = false);
		void draw(const SDL_Rect& source, const Vector2& position, float angle = 0, const Vector2& scale = { 1, 1 }, const Vector2 & origin = Vector2::zero, bool flip = false);

		Vector2 getSize();
		

	protected:
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* renderer{ nullptr };
	};
}