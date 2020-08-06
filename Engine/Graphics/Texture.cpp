#include "pch.h"
#include "Texture.h"

namespace ew {
	bool Texture::create(const std::string& name, SDL_Renderer* _renderer) {
		renderer = _renderer;
		SDL_Surface* surface = IMG_Load(name.c_str());
		if (surface == nullptr) {
			std::cout << "Error: " << SDL_GetError() << std::endl;
			return false;
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture == nullptr) {
			std::cout << "Error: " << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}

	void Texture::destroy() {

	}

	void Texture::draw(const Vector2& position, const Vector2& scale, float angle) {
		Vector2 size = getSize();
		size *= scale;

		SDL_Rect rect;
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);
		SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
	}
	Vector2 Texture::getSize() {
		SDL_Point point;
		SDL_QueryTexture(texture, NULL, NULL, &point.x, &point.y);

		return { point.x, point.y };
	}
}

