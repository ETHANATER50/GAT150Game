#pragma once

#include "Math/Vector2.h"
#include <SDL.h>
#include <string>

namespace ew {
	class Texture {
	public:
		bool create(const std::string& name, SDL_Renderer* _renderer);
		void destroy();

		void draw(const Vector2& position, const Vector2& scale, float angle);

		Vector2 getSize();
		

	protected:
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* renderer{ nullptr };
	};
}