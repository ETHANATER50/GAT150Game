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

		void draw(const Vector2& position, const Vector2& scale = { 1, 1 }, float angle = 0);
		void draw(const SDL_Rect& source, const Vector2& position, const Vector2& scale = { 1, 1 }, float angle = 0);

		Vector2 getSize();
		

	protected:
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* renderer{ nullptr };
	};
}